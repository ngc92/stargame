#include "CWorldBase.h"
#include "../IGameObject.h"
#include "../WorldAction.h"
#include "../IGameViewModule.h"
#include "util/algos.h"
#include <Box2D/Dynamics/b2World.h>
#include <iostream>

namespace game
{
	CWorldBase::CWorldBase() : mPhysicWorld( std::make_unique<b2World>(b2Vec2(0,0)) )
	{
		mPhysicWorld->SetAutoClearForces( false );
		mPhysicWorld->SetContinuousPhysics( true );
	}
	
	CWorldBase::~CWorldBase()
	{
		// ensure all physic bodies are destroyed in-game before we remove the b2World
		mGameObjects.clear();
		mSpawnQueue.clear();
	}
	
	/// adds a listener that is called whenever a new game objects is spawned in the world.
	ListenerRef CWorldBase::addSpawnListener(std::function<void(IGameObjectView&)> f)
	{
		return mSpawnListeners.addListener(f);
	}
	
	void CWorldBase::perform_spawning()
	{
		// spawn new objects
		for(auto& obj : mSpawnQueue)
		{
			mGameObjects.push_back( std::move(obj) );
			mSpawnListeners.notify( *mGameObjects.back() );
		}
		mSpawnQueue.clear();
	}
	
	std::size_t CWorldBase::object_count() const
	{
		return mGameObjects.size();
	}

	/// iterates over all game objects \p o inside this world and calls \p f(o).
	void CWorldBase::iterateAllObjects(const std::function<void(IGameObjectView&)>& f) const
	{
		for(auto& o : mGameObjects)
		{
			f(*o);
		}
	}
	
	void CWorldBase::addGameObject(std::shared_ptr<IGameObject> object)
	{
		// check uniqueness
		assert( std::none_of(begin(mGameObjects), end(mGameObjects), [id=object->id()](auto& o){ return o->id() == id; }) );
		assert( std::none_of(begin(mSpawnQueue), end(mSpawnQueue), [id=object->id()](auto& o){ return o->id() == id; }) );
		mSpawnQueue.push_back( std::move(object) );
	}

	/// get a game object that fulfills a predicate. Searches both 
	/// current objects and spawn list.
	template<class F>
	IGameObject& CWorldBase::getObjectByPredicate( F&& function )
	{
		auto found = std::find_if(begin(mGameObjects), end(mGameObjects), function);
		if( found == end(mGameObjects))
		{
			// maybe the object still waits to be added to the world.
			auto not_spawned_yet = std::find_if(begin(mSpawnQueue), end(mSpawnQueue), function);
			if( not_spawned_yet == end(mSpawnQueue))
			{
				std::cerr << "requested object not found!\n";
				assert(0);
			}
			return **not_spawned_yet;
		}
		return **found;
	}
	
	IGameObject& CWorldBase::getObjectByID( uint64_t id )
	{
		return getObjectByPredicate([id](auto& o){ return o->id() == id; });
	}
	
	/// get a game object view with specified name. If more than
	/// one object exists with the given name, it is unspecified 
	/// which one is returned (i.e. don't do that!).
	IGameObject& CWorldBase::getObjectByName( const std::string& name )
	{
		return getObjectByPredicate([&name](auto& o){ return o->name() == name; });
	}
	
	/// gets an id that is currently not used by any game object.
	uint64_t CWorldBase::getNextFreeID()
	{
		while(true)
		{
			++mFreeIDCandidate;
			
			if(std::any_of(begin(mGameObjects), end(mGameObjects), [id=mFreeIDCandidate](auto& o){ return o->id() == id; }))
				continue;
		
			if(std::any_of(begin(mSpawnQueue), end(mSpawnQueue), [id=mFreeIDCandidate](auto& o){ return o->id() == id; }))
				continue;
			
			// ok, we're good to go
			return mFreeIDCandidate;
		}
	}
	
	void CWorldBase::clear_objects()
	{
		remove_if(mGameObjects, [](const auto& o){ return !o->isAlive(); });
	}

	/// get a pointer to the internal world
	const b2World& CWorldBase::world() const
	{
		return *mPhysicWorld;
	}
	
	b2World& CWorldBase::getWorld()
	{
		return *mPhysicWorld;
	}
	
	void CWorldBase::addModule(std::weak_ptr<IGameViewModule> module)
	{
		auto locked = module.lock();
		if(locked)
		{
			locked->init( *this );
			mViewModules.push_back( std::move(module) );
		}
	}
	
	void CWorldBase::update_view_modules()
	{
		for(auto& mod : mViewModules)
		{
			auto locked = mod.lock();
			if(locked)
			{
				locked->step( *this );
			}
		}
		
		remove_expired(mViewModules);
	}
	
	void CWorldBase::update_game_objects(const spawn::ISpawnManager& spawner)
	{
		std::vector<WorldActionQueue::action_fn> action_queue;
		WorldActionQueue push_action(action_queue);

		// update all objects
		for(auto& obj : mGameObjects)
		{
			if(obj->isAlive())
			{
				obj->step( *this, push_action );
				obj->onStep( *this );
			}
		}

		for(auto& a : action_queue)
			a(*this, spawner);

		clear_objects();
	}
	
	/// calls onStep for all game objects
	void CWorldBase::notify_game_objects( )
	{
		for(auto& obj : mGameObjects)
		{
			if(obj->isAlive())
			{
				obj->onStep( *this );
			}
		}
	}
}

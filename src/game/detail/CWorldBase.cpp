#include "CWorldBase.h"
#include "../IGameObject.h"
#include "../WorldAction.h"
#include "../IGameViewModule.h"
#include "physics/CPhysicsThread.h"
#include "physics/events/SpawnEvent.h"
#include "physics/events/ObjectUpdateEvent.h"
#include "physics/events/CollisionEvent.h"
#include "util/algos.h"
#include <iostream>

namespace game
{
	CWorldBase::CWorldBase() : mPhysics( new ::physics::detail::CPhysicsThread )
	{
		mPhysics->start();
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
	boost::optional<IGameObject&> CWorldBase::getObjectByPredicate( F&& function )
	{
		auto found = std::find_if(begin(mGameObjects), end(mGameObjects), function);
		if( found == end(mGameObjects))
		{
			// maybe the object still waits to be added to the world.
			auto not_spawned_yet = std::find_if(begin(mSpawnQueue), end(mSpawnQueue), function);
			if( not_spawned_yet == end(mSpawnQueue))
			{
				return boost::none;
			}
			return **not_spawned_yet;
		}
		return **found;
	}
	
	IGameObject& CWorldBase::getObjectByID( uint64_t id )
	{
		auto object = getObjectByPredicate([id](auto& o){ return o->id() == id; });
		if(!object)
			throw( std::exception() );
		return object.get();
	}
	
	/// get the game object view with specified id.
	IGameObject* CWorldBase::getObjectPtrByID( uint64_t id )
	{
		auto object = getObjectByPredicate([id](auto& o){ return o->id() == id; });
		if(!object)
			return nullptr;
		return &object.get();
	}
	
	/// get a game object view with specified name. If more than
	/// one object exists with the given name, it is unspecified 
	/// which one is returned (i.e. don't do that!).
	IGameObject& CWorldBase::getObjectByName( const std::string& name )
	{
		auto object = getObjectByPredicate([&name](auto& o){ return o->name() == name; });
		if(!object)
			throw( std::exception() );
		return object.get();
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
		/// \todo remove associated body
		remove_if(mGameObjects, [](const auto& o){ return !o->isAlive(); });
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
		
		// get update events
		const auto& events = getPhysicsThread().getEvents();
		std::cout << events.size() << "\n";
		for(auto& ev : events )
		{
			std::cout << "event " << ev.type().name() <<"\n";
		}

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
	
	::physics::IPhysicsThread& CWorldBase::getPhysicsThread()
	{
        return *mPhysics;
	}
    
    const ::physics::IPhysicsThread& CWorldBase::getPhysicsThread() const
    {
        return *mPhysics;
    }
}

#include "CWorldBase.h"
#include "../IGameObject.h"
#include "../WorldAction.h"
#include "../IGameViewModule.h"
#include "util/algos.h"
#include <Box2D/Dynamics/b2World.h>

namespace game
{
	CWorldBase::CWorldBase() : mPhysicWorld( std::make_unique<b2World>(b2Vec2(0,0)) )
	{
		mPhysicWorld->SetAutoClearForces( false );
		mPhysicWorld->SetContinuousPhysics( true );
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
		assert( std::find_if(begin(mGameObjects), end(mGameObjects), [id=object->id()](auto& o){ return o->id() == id; }) == end(mGameObjects) );
		assert( std::find_if(begin(mSpawnQueue), end(mSpawnQueue), [id=object->id()](auto& o){ return o->id() == id; }) == end(mSpawnQueue) );
		mSpawnQueue.push_back( std::move(object) );
	}

	IGameObject& CWorldBase::getObjectByID( uint64_t id )
	{
		auto found = std::find_if(begin(mGameObjects), end(mGameObjects), [id](auto& o){ return o->id() == id; });
		if( found == end(mGameObjects))
		{
			// maybe the object still waits to be added to the world.
			auto not_spawned_yet = std::find_if(begin(mSpawnQueue), end(mSpawnQueue), [id](auto& o){ return o->id() == id; });
			if( not_spawned_yet == end(mSpawnQueue))
				assert(0);
			return **not_spawned_yet;
		}
		return **found;
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
}

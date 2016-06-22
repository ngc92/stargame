#include "CGameWorld.h"
#include "../IGameObject.h"
#include "../WorldAction.h"
#include "../spawn/ISpawnManager.h"
#include "../IGameViewModule.h"
#include "../physics/ContactListener.h"
#include <Box2D/Dynamics/b2World.h>
#include <algorithm>
#include <iostream>

namespace game
{
	CGameWorld::CGameWorld() : mPhysicWorld( std::make_unique<b2World>(b2Vec2(0,0)) ),
							 mContactListener( std::make_unique<ContactListener>() )
	{
		mPhysicWorld->SetAutoClearForces( false );
		mPhysicWorld->SetContactListener( mContactListener.get() );
		mPhysicWorld->SetContactFilter( mContactListener.get() );
		mPhysicWorld->SetContinuousPhysics( true );
	}

	CGameWorld::~CGameWorld()
	{
	}

	void CGameWorld::step(const spawn::ISpawnManager& spawner)
	{
		// do actually 2 physic steps per loop step.
		// this makes it possible for bodies to move faster.
		constexpr const int SUB_STEPS = 2;
		// step the physic world
		for(int i = 0; i < SUB_STEPS; ++i)
		{
			mPhysicWorld->Step(1.0/60 / SUB_STEPS, 8, 3);
			// and trigger corresponding physic events
			mContactListener->triggerEvents();
		}
		mPhysicWorld->ClearForces();

		std::vector<WorldActionQueue::action_fn> action_queue;
		WorldActionQueue push_action(action_queue);

		// update all objects
		for(auto& obj : mGameObjects)
		{
			if(obj->isAlive())	obj->onStep( *this, push_action );
		}

		for(auto& a : action_queue)
			a(*this, spawner);

		clear_objects();

		// spawn new objects
		for(auto& obj : mSpawnQueue)
		{
			mGameObjects.push_back( std::move(obj) );
			mSpawnListeners.notify( *mGameObjects.back() );
		}
		mSpawnQueue.clear();

		// finally, update all modules
		for(auto& mod : mModules)
		{
			auto locked = mod.lock();
			if(locked)
			{
				locked->step( *this, spawner );
			}
		}

		auto nlast = remove_if(begin(mModules), end(mModules), [](const auto& o){ return o.expired(); });
		mModules.resize(distance(begin(mModules), nlast));

		// fuck, this stuff need refactoring.
		for(auto& mod : mViewModules)
		{
			auto locked = mod.lock();
			if(locked)
			{
				locked->step( *this );
			}
		}

		auto nlast2 = remove_if(begin(mViewModules), end(mViewModules), [](const auto& o){ return o.expired(); });
		mViewModules.resize(distance(begin(mViewModules), nlast2));
	}

	void CGameWorld::clear_objects()
	{
		using namespace std;
		auto nlast = remove_if(begin(mGameObjects), end(mGameObjects), [](const std::shared_ptr<IGameObject>& o){ return !o->isAlive(); });
		mGameObjects.resize(distance(begin(mGameObjects), nlast));
	}

	void CGameWorld::addGameObject(std::shared_ptr<IGameObject> object)
	{
		// check uniqueness
		assert( std::find_if(begin(mGameObjects), end(mGameObjects), [id=object->id()](auto& o){ return o->id() == id; }) == end(mGameObjects) );
		assert( std::find_if(begin(mSpawnQueue), end(mSpawnQueue), [id=object->id()](auto& o){ return o->id() == id; }) == end(mSpawnQueue) );
		mSpawnQueue.push_back( std::move(object) );
	}

	IGameObject& CGameWorld::getObjectByID( uint64_t id )
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

	const b2World* CGameWorld::world() const
	{
		return mPhysicWorld.get();
	}

	b2World* CGameWorld::getWorld()
	{
		return mPhysicWorld.get();
	};

	std::size_t CGameWorld::object_count() const
	{
		return mGameObjects.size();
	}

	/// adds a listener that is called whenever a new game objects is spawned in the world.
	ListenerRef CGameWorld::addSpawnListener(std::function<void(IGameObjectView&)> f)
	{
		return mSpawnListeners.addListener(f);
	}

	/// iterates over all game objects \p o inside this world and calls \p f(o).
	void CGameWorld::iterateAllObjects(const std::function<void(IGameObjectView&)>& f) const
	{
		for(auto& o : mGameObjects)
		{
			f(*o);
		}
	}

	void CGameWorld::addModule(std::weak_ptr<IGameModule> module)
	{
		auto locked = module.lock();
		if(locked)
		{
			locked->init( *this );
			mModules.push_back( std::move(module) );
		}
	}

	void CGameWorld::addModule(std::weak_ptr<IGameViewModule> module)
	{
		auto locked = module.lock();
		if(locked)
		{
			locked->init( *this );
			mViewModules.push_back( std::move(module) );
		}
	}

	// -----------------------------------------------------------
	//			constructor function
	// -----------------------------------------------------------
	std::unique_ptr<IGameWorld> createGameWorld()
	{
		return std::make_unique<CGameWorld>();
	}
}

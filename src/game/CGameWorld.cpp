#include "CGameWorld.h"
#include "IGameObject.h"
#include "WorldAction.h"
#include "spawn/ISpawnManager.h"
#include "ContactListener.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <algorithm>
#include <iostream>

namespace game
{
	CGameWorld::CGameWorld() : mPhysicWorld( std::make_unique<b2World>(b2Vec2(0,0)) ),
							 mContactListener( std::make_unique<ContactListener>() )
	{
		mPhysicWorld->SetAutoClearForces( true );
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
	}

	void CGameWorld::clear_objects()
	{
		using namespace std;
		auto nlast = remove_if(begin(mGameObjects), end(mGameObjects), [](const std::shared_ptr<IGameObject>& o){ return !o->isAlive(); });
		mGameObjects.resize(distance(begin(mGameObjects), nlast));
	}

	void CGameWorld::addGameObject(std::shared_ptr<IGameObject> object)
	{
		mSpawnQueue.push_back( std::move(object) );
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
}

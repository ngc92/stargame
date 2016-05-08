#include "CGameWorld.h"
#include "IGameObject.h"
#include "ContactListener.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <algorithm>
#include <iostream>

namespace game
{
	CGameWorld::CGameWorld() : mPhysicWorld( make_unique<b2World>(b2Vec2(0,0)) ),
							 mContactListener( make_unique<ContactListener>() )
	{
		mPhysicWorld->SetAutoClearForces( true );
		mPhysicWorld->SetContactListener( mContactListener.get() );
		mPhysicWorld->SetContinuousPhysics( true );
	}

	CGameWorld::~CGameWorld()
	{
	}

	void CGameWorld::step()
	{
		// step the physic world
		mPhysicWorld->Step(1.0/60, 8, 3);
		// and trigger corresponding physic events
		mContactListener->triggerEvents();

		// update all objects
		for(auto& obj : mGameObjects)
		{
			if(obj->isAlive())	obj->onStep( );
		}

		clear_objects();
	}

	void CGameWorld::clear_objects()
	{
		using namespace std;
		auto nlast = remove_if(begin(mGameObjects), end(mGameObjects), [](const std::shared_ptr<IGameObject>& o){ return !o->isAlive(); });
		mGameObjects.resize(distance(begin(mGameObjects), nlast));
	}

	void CGameWorld::addGameObject(std::shared_ptr<IGameObject> object)
	{
		mGameObjects.push_back( object );
		mSpawnListeners.notify(*object);
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

#include "GameWorld.h"
#include "GameObject.h"
#include "ContactListener.h"
#include <algorithm>

namespace game
{
	GameWorld::GameWorld() : mPhysicWorld( make_unique<b2World>(b2Vec2(0,0)) ),
							 mContactListener( make_unique<ContactListener>() )
	{
		mPhysicWorld->SetAutoClearForces( true );
		mPhysicWorld->SetContactListener( mContactListener.get() );
		mPhysicWorld->SetContinuousPhysics( true );
	}

	GameWorld::~GameWorld()
	{
	}

	void GameWorld::step(float dt)
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

	void GameWorld::clear_objects()
	{
		using namespace std;
		auto nlast = remove_if(begin(mGameObjects), end(mGameObjects), [](const std::shared_ptr<GameObject>& o){ return !o->isAlive(); });
		mGameObjects.resize(distance(begin(mGameObjects), nlast));
	}

	void GameWorld::addGameObject(std::shared_ptr<GameObject> object)
	{
		mGameObjects.push_back( object );
	}
}

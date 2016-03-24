#include "GameWorld.h"
#include "GameObject.h"
#include <algorithm>

namespace game
{
	void GameWorld::step(float dt)
	{
		// step the physic world
		mPhysicWorld->Step(1.0/60, 8, 3);

		// update all objects
		for(auto& obj : mGameObjects)
		{
			if(obj->isAlive())	obj->step( );
		}

		clear_objects();
	}

	void GameWorld::clear_objects()
	{
		using namespace std;
		auto nlast = remove_if(begin(mGameObjects), end(mGameObjects), [](const std::shared_ptr<GameObject>& o){ return o->isAlive(); });
		mGameObjects.resize(distance(begin(mGameObjects), nlast));
	}
}

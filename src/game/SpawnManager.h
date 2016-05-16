#ifndef SPAWNMANAGER_H_INCLUDED
#define SPAWNMANAGER_H_INCLUDED

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "fwd.h"
#include <Box2D/Common/b2Math.h>

class b2Body;

namespace game
{
	class IGameWorld;
	namespace spawn
	{
		class IDataManager;
	}

	struct SpawnInitData
	{
		SpawnInitData(IGameWorld& wd, std::string tp, b2Vec2 pos = b2Vec2_zero, b2Vec2 vel = b2Vec2_zero) :
			world(wd), type(std::move(tp)), position( std::move(pos) ), velocity( std::move(vel) )
		{}
		IGameWorld& world;
		std::string type;
		b2Vec2 position = b2Vec2(0, 0);
		b2Vec2 velocity = b2Vec2(0,0);
		float angle = 0.f;
		float angular_velocity = 0.f;
	};

	class SpawnManager
	{
	public:
		SpawnManager();
		~SpawnManager();

		static SpawnManager& singleton();

		std::shared_ptr<IGameObject> createSpaceShip( const SpawnInitData& data, int team, long id = -1 );
		std::shared_ptr<IGameObject> createBullet( SpawnInitData data, IGameObject& shooter );
	private:
		std::unique_ptr<spawn::IDataManager> mDataManager;
		static SpawnManager* mSingleton;
	};
}

#endif // SPAWNMANAGER_H_INCLUDED

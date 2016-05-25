#ifndef ISPAWNMANAGER_H_INCLUDED
#define ISPAWNMANAGER_H_INCLUDED

#include <memory>
#include <string>
#include "fwd.h"
#include <Box2D/Common/b2Math.h>

class b2Body;

namespace game
{
	class IGameWorld;

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

	class ISpawnManager
	{
	public:
		ISpawnManager()
		{
			assert( mSingleton == nullptr );
			mSingleton = this;
		}

		virtual ~ISpawnManager()
		{
			mSingleton = nullptr;
		}

		static ISpawnManager& singleton() { return *mSingleton; }

		virtual std::shared_ptr<IGameObject> createSpaceShip( const SpawnInitData& data, int team, long id = -1 ) = 0;
		virtual std::shared_ptr<IGameObject> createBullet( SpawnInitData data, IGameObject& shooter ) = 0;
	private:

		static ISpawnManager* mSingleton;
	};
}

#endif // ISPAWNMANAGER_H_INCLUDED

#ifndef SPAWNMANAGER_H_INCLUDED
#define SPAWNMANAGER_H_INCLUDED

#include "ISpawnManager.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "game/fwd.h"

namespace physics
{
namespace actions
{
    class SpawnObject;
}
}

namespace game
{
namespace spawn
{
	class IDataManager;

	class CSpawnManager : public ISpawnManager
	{
	public:
		CSpawnManager();
		~CSpawnManager();

		std::shared_ptr<IGameObject> spawn( IGameWorld& world, const SpawnData& data ) const override;

		void makeSpaceShip( IGameObject& object, int team, ::physics::actions::SpawnObject& spac ) const;
		void makeBullet( IGameObject& object, const IGameObject* shooter, ::physics::actions::SpawnObject& spac ) const;
	private:
		std::unique_ptr<IDataManager> mDataManager;
	};
}
}

#endif // SPAWNMANAGER_H_INCLUDED

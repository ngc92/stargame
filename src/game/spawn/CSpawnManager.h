#ifndef SPAWNMANAGER_H_INCLUDED
#define SPAWNMANAGER_H_INCLUDED

#include "ISpawnManager.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "game/fwd.h"

class b2Body;

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

		void makeSpaceShip( IGameObject& object, int team ) const;
		void makeBullet( IGameObject& object, const IGameObject& shooter ) const;
	private:
		std::unique_ptr<IDataManager> mDataManager;
	};
}
}

#endif // SPAWNMANAGER_H_INCLUDED

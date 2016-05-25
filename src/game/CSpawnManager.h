#ifndef SPAWNMANAGER_H_INCLUDED
#define SPAWNMANAGER_H_INCLUDED

#include "ISpawnManager.h"

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

	class CSpawnManager : public ISpawnManager
	{
	public:
		CSpawnManager();
		~CSpawnManager();

		std::shared_ptr<IGameObject> createSpaceShip( const SpawnInitData& data, int team, long id = -1 ) override;
		std::shared_ptr<IGameObject> createBullet( SpawnInitData data, IGameObject& shooter ) override;
	private:
		std::unique_ptr<spawn::IDataManager> mDataManager;
	};
}

#endif // SPAWNMANAGER_H_INCLUDED

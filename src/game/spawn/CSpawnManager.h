#ifndef SPAWNMANAGER_H_INCLUDED
#define SPAWNMANAGER_H_INCLUDED

#include "game/ISpawnManager.h"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "game/fwd.h"
#include <Box2D/Common/b2Math.h>

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
		
		std::shared_ptr<IGameObject> spawn( IGameWorld& world, const SpawnData& data ) override;

		void makeSpaceShip( const std::string& type, IGameObject& object, int team );
		void makeBullet( const std::string& type, IGameObject& object, const IGameObject& shooter );
	private:
		std::unique_ptr<IDataManager> mDataManager;
	};
}
}

#endif // SPAWNMANAGER_H_INCLUDED

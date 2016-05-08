#ifndef SPAWNMANAGER_H_INCLUDED
#define SPAWNMANAGER_H_INCLUDED

#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include "fwd.h"
#include <Box2D/Common/b2Math.h>

class b2Body;

namespace game
{
	namespace spawn
	{
		class IDataManager;
	}

	class SpawnManager
	{
	public:
		SpawnManager(std::function<b2Body*()> bodysource);
		~SpawnManager();

		std::shared_ptr<IGameObject> createSpaceShip( const std::string& type, long id = -1 );
	private:
		std::function<b2Body*()> mBodyFactory;
		std::unique_ptr<spawn::IDataManager> mDataManager;
	};
}

#endif // SPAWNMANAGER_H_INCLUDED

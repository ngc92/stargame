#ifndef SPAWNMANAGER_H_INCLUDED
#define SPAWNMANAGER_H_INCLUDED

#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include "fwd.h"

class b2Body;

namespace game
{
	class SpawnManager
	{
	public:
		SpawnManager(std::function<b2Body*()> bodysource);

		std::shared_ptr<GameObject> createSpaceShip( const std::string& type, long id = -1 );
		std::shared_ptr<IComponent> createComponent( const std::string& type );
	private:
		std::function<b2Body*()> mBodyFactory;

		struct CData
		{
			std::size_t cell;
			std::string type;
		};
		typedef std::vector<CData> ShipDef;

		std::unordered_map<std::string, ShipDef> mShipDefinitions;
	};
}

#endif // SPAWNMANAGER_H_INCLUDED

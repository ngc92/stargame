#include "SpawnManager.h"

#include "components/FuelTank.h"
#include "components/Engine.h"
#include "SpaceShip.h"
#include "ShipStructure.h"
#include <Box2D/Box2D.h>
#include <cassert>

namespace game
{
	SpawnManager::SpawnManager(std::function<b2Body*()> bodysource) :
		mBodyFactory( std::move(bodysource) )
	{
		mShipDefinitions["PLAYER"] = ShipDef{CData{0, "Engine"}, CData{0, "FuelTank"}};
	}

	std::shared_ptr<IComponent> SpawnManager::createComponent(const std::string& type)
	{
		/// \todo replace with factory interface
		if(type == "FuelTank")
		{
            return std::make_shared<components::FuelTank>();
		} else if(type == "Engine")
		{
            return std::make_shared<components::Engine>();
		}
		assert(0);
	}

	std::shared_ptr<GameObject> SpawnManager::createSpaceShip( const std::string& type, long id )
	{
		auto structure = make_unique<ShipStructure>();
		auto& dat = mShipDefinitions.at(type);
		for(CData& c : dat)
		{
			structure->addComponent(c.cell, createComponent(c.type));
		}

		return std::make_shared<SpaceShip>( id, mBodyFactory(), std::move(structure) );
	}
}

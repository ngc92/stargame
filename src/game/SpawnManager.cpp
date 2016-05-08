#include "SpawnManager.h"

#include "spawn/factory.h"
#include "spawn/CDataManager.h"

#include "CGameObject.h"
#include "object_module/ArmourSegment.h"
#include "object_module/CSubStructure.h"
#include "object_module/CFlightModel.h"
#include <Box2D/Box2D.h>
#include <cassert>

#include <boost/property_tree/ptree.hpp>

namespace game
{
	SpawnManager::SpawnManager(std::function<b2Body*()> bodysource) :
		mBodyFactory( std::move(bodysource) ),
		mDataManager(make_unique<spawn::CDataManager>() )
	{
		mDataManager->loadFile("data/components.xml");
		mDataManager->loadFile("data/hulls.xml");
		mDataManager->loadFile("data/ships.xml");
	}

	SpawnManager::~SpawnManager()
	{

	}

	std::shared_ptr<IGameObject> SpawnManager::createSpaceShip( const std::string& type, long id )
	{
		auto ship = std::make_shared<CGameObject>(mBodyFactory(), id);
		auto& dat = mDataManager->getShipData(type);
		auto structure = mDataManager->getHullData( dat.hull() ).create();

		for(auto& c : dat.components())
		{
			auto cell = structure->getCellByID(c.cell);
			if(!cell)
				BOOST_THROW_EXCEPTION(std::runtime_error("could not find specified cell."));
			auto new_comp = mDataManager->getComponentData(c.type).create();
			cell->addComponent( new_comp );
		}

		ship->addModule( structure );
		ship->addModule( std::make_shared<CFlightModel>() );

		/// \todo only call this after adding to the world!
		ship->onInit();

		return ship;
	}
}

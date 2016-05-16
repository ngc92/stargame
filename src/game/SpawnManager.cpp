#include "SpawnManager.h"

#include "spawn/factory.h"
#include "spawn/CDataManager.h"

#include "CGameObject.h"
#include "property/CProperty.h"
#include "IGameWorld.h"
#include "object_module/ArmourSegment.h"
#include "object_module/CSubStructure.h"
#include "object_module/CFlightModel.h"
#include "object_module/CAffiliation.h"
#include <Box2D/Box2D.h>
#include <cassert>

#include <boost/property_tree/ptree.hpp>

namespace game
{
	SpawnManager::SpawnManager() :
		mDataManager(make_unique<spawn::CDataManager>() )
	{
		mDataManager->loadFile("data/components.xml");
		mDataManager->loadFile("data/hulls.xml");
		mDataManager->loadFile("data/ships.xml");
		mDataManager->loadFile("data/projectiles.xml");

		assert( mSingleton == nullptr );
		mSingleton = this;
	}

	SpawnManager::~SpawnManager()
	{
		mSingleton = nullptr;
	}

	SpawnManager* SpawnManager::mSingleton = nullptr;
	SpawnManager& SpawnManager::singleton()
	{
		return *mSingleton;
	}

	b2Body* init_body(const SpawnInitData& data)
	{
		b2BodyDef def;
		def.angle = data.angle;
		def.position = data.position;
		def.linearVelocity = data.velocity;
		def.angularVelocity = data.angular_velocity;
		def.type = b2_dynamicBody;
		return data.world.getWorld()->CreateBody(&def);
	}

	std::shared_ptr<IGameObject> SpawnManager::createSpaceShip( const SpawnInitData& data, int team, long id )
	{
		auto ship = std::make_shared<CGameObject>(init_body(data), id);
		auto& dat = mDataManager->getShipData(data.type);
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
		ship->addModule( std::make_shared<CFlightModel>( 1.0 ) );
		ship->addModule( std::make_shared<CAffiliation>( team ) );
		
		ship->addProperty( property::CProperty::create("_type_", ship.get(), std::string("ship")) );
		dat.addAttributes( *ship );

		// add gfx data
		ship->onInit(data.world);
		data.world.addGameObject(ship);


		return ship;
	}

	std::shared_ptr<IGameObject> SpawnManager::createBullet( SpawnInitData data, IGameObject& shooter )
	{
		auto& dat = mDataManager->getProjectileData( data.type );

		// transform shot coordinates
		data.position = shooter.body()->GetWorldVector( data.position ) + shooter.position();
		data.velocity = shooter.body()->GetWorldVector( data.velocity + b2Vec2(dat.propellVelocity(), 0) ) + shooter.velocity();
		data.angle += shooter.angle();

		auto bullet = std::make_shared<CGameObject>(init_body(data), -2);
		bullet->addModule( std::make_shared<CFlightModel>( 100.0 ) );
		auto shared = shooter.shared_from_this();
		bullet->addModule( std::make_shared<CAffiliation>( shared ) );

		// add circular fixture
		b2CircleShape shape;
		shape.m_radius = dat.radius();
		/// \todo set density for mass!
		bullet->getBody()->CreateFixture( &shape, 1.0 );
		bullet->getBody()->SetBullet(true);
		
		bullet->addProperty( property::CProperty::create("_type_", bullet.get(), std::string("bullet")) );

		bullet->onInit(data.world);
		data.world.addGameObject(bullet);

		return bullet;
	}
}

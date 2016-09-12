#include "CSpawnManager.h"

#include "CDataManager.h"
#include "SpawnData.h"
#include "game/physics/body.h"
#include "game/physics/convert.h"
#include "game/physics/fixture.h"
#include "game/physics/shape.h"
#include "game/physics/ContactFilter.h"

#include "physics/actions/SpawnObject.h"
#include "physics/data/Body.h"

#include "game/IGameObject.h"
#include "property/CProperty.h"
#include "game/IGameWorld.h"
#include "game/object_module/ArmourSegment.h"
#include "game/object_module/CSubStructure.h"
#include "game/object_module/CFlightModel.h"
#include "game/object_module/CAffiliation.h"
#include "game/object_module/CTimedDeletion.h"
#include "game/object_module/CImpactDamageSource.h"
#include <cassert>
#include <iostream>

#include <boost/property_tree/ptree.hpp>

namespace game
{
namespace spawn
{
	CSpawnManager::CSpawnManager() :
		mDataManager(std::make_unique<spawn::CDataManager>() )
	{
		mDataManager->loadFile("data/components.xml");
		mDataManager->loadFile("data/hulls.xml");
		mDataManager->loadFile("data/ships.xml");
		mDataManager->loadFile("data/projectiles.xml");
	}

	CSpawnManager::~CSpawnManager(){}

	std::shared_ptr<IGameObject> CSpawnManager::spawn( IGameWorld& world, const SpawnData& data ) const
	{
		// create the body to be used
		uint64_t new_id = data.id == -1 ? world.getNextFreeID() : data.id;
		
		auto game_object = createGameObject(new_id, data.type, data.category, nullptr);

        ::physics::data::BodyDef bdef(data.position, data.velocity, data.angle, data.angular_velocity);
		::physics::actions::SpawnObject spob;

		if(data.category == ObjectCategory::SPACESHIP)
		{
			makeSpaceShip(*game_object, 1, spob);
		}
		else if( data.category == ObjectCategory::BULLET )
		{
			makeBullet(*game_object, data.origin, spob);
        }
        
        // push spawn body action to physics world
		spob.body = std::move(bdef);
		world.getPhysicsThread().pushAction( std::move(spob) );
        
		game_object->onInit(world);
		world.addGameObject( game_object );
		return game_object;
	}

	void CSpawnManager::makeSpaceShip( IGameObject& object,  int team, ::physics::actions::SpawnObject& spob ) const
	{
		auto& dat = mDataManager->getShipData( object.type() );
		auto structure = mDataManager->getHullData( dat.hull() ).create();
		spob.fixtures = structure->getFixtures();
		
		spob.setLinearDamping( 0.0 );
        spob.setAngularDamping( 1 );

		for(auto& c : dat.components())
		{
			auto cell = structure->getCellByID(c.cell);
			if(!cell)
				BOOST_THROW_EXCEPTION(std::runtime_error("could not find specified cell."));
			auto new_comp = mDataManager->getComponentData(c.type).create();
			cell->addComponent( new_comp );
		}

		object.addModule( structure );
		object.addModule( std::make_shared<CFlightModel>( 1.0, 0.2 ) );
		object.addModule( std::make_shared<CAffiliation>( team ) );
		object.addModule( std::make_shared<CImpactDamageSource>( 0.01, 1.0 ) );
		dat.addAttributes( object );
	}

	void CSpawnManager::makeBullet( IGameObject& object, const IGameObject* shooter, ::physics::actions::SpawnAction& spac ) const
	{
		auto& dat = mDataManager->getProjectileData( object.type() );

		object.addModule( std::make_shared<CFlightModel>( 100.0, 0.f ) );
		object.addModule( std::make_shared<CTimedDeletion>( dat.lifetime() ) );
		if(shooter)
		{
			auto shared = std::const_pointer_cast<IGameObjectView>(shooter->shared_from_this());
			object.addModule( std::make_shared<CAffiliation>( shared ) );
		}
		object.addModule( std::make_shared<CImpactDamageSource>( 0.5, 0.5 ) );

		// add circular fixture
		/// \todo set density for mass!
		::physics::data::CircleShape shape(dat.radius);
        ::physics::data::Fixture f( shape );
        f.setRestitution( 0.5 );
        f.setDensity( 1 );
        bdef.setBullet(true);
        spob.fixtures.push_back( std::move(f) );
        
        /// \todo transform propell velocity into world frame and add
        /// \todo set collision blacklist shooter
	}
}
}

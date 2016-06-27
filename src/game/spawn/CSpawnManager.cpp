#include "CSpawnManager.h"

#include "CDataManager.h"
#include "SpawnData.h"
#include "game/physics/body.h"
#include "game/physics/convert.h"
#include "game/physics/fixture.h"

#include "game/IGameObject.h"
#include "property/CProperty.h"
#include "game/IGameWorld.h"
#include "game/object_module/ArmourSegment.h"
#include "game/object_module/CSubStructure.h"
#include "game/object_module/CFlightModel.h"
#include "game/object_module/CAffiliation.h"
#include "game/object_module/CTimedDeletion.h"
#include "game/object_module/CImpactDamageSource.h"
#include <Box2D/Box2D.h>
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
		b2BodyDef def = body_def(data);
		def.type = b2_dynamicBody;
		auto body = world.getWorld().CreateBody(&def);
		uint64_t new_id = data.id == -1 ? world.getNextFreeID() : data.id;
		auto game_object = createGameObject(new_id, data.type, data.category, body);

		if(data.category == ObjectCategory::SPACESHIP)
			makeSpaceShip(*game_object, 1);
		else if( data.category == ObjectCategory::BULLET )
			makeBullet(*game_object, data.origin);

		game_object->onInit(world);
		world.addGameObject( game_object );
		return game_object;
	}

	void CSpawnManager::makeSpaceShip( IGameObject& object,  int team ) const
	{
		auto& dat = mDataManager->getShipData( object.type() );
		auto structure = mDataManager->getHullData( dat.hull() ).create();

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

	void CSpawnManager::makeBullet( IGameObject& object, const IGameObject* shooter ) const
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
		b2CircleShape shape;
		shape.m_radius = dat.radius();
		b2FixtureDef def;
		def.density = 1.0;
		def.restitution = 0.5;
		def.shape = &shape;
		/// \todo set density for mass!
		auto fix = physics::Fixture::create(object.getBody(), def);
		object.getBody().body()->SetBullet(true);
		object.getBody().addLinearVelocity( world_vector(object.body(), b2Vec2(dat.propellVelocity(), 0) ) );
		if(shooter)
			object.setIgnoreCollisionTarget( shooter->body().body() );
	}
}
}

#include "CSpawnManager.h"

#include "CDataManager.h"
#include "SpawnData.h"

#include "game/CGameObject.h"
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
		auto body = world.getWorld()->CreateBody(&def);
		auto game_object = std::make_shared<CGameObject>(body, data.id);

		if(data.category == SpawnType::SPACESHIP)
			makeSpaceShip(data.type, *game_object, 1);
		else if( data.category == SpawnType::BULLET )
			makeBullet(data.type, *game_object, *data.origin);

		game_object->onInit(world);
		world.addGameObject( game_object );
		return game_object;
	}

	void CSpawnManager::makeSpaceShip( const std::string& type, IGameObject& object,  int team ) const
	{
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

		object.addModule( structure );
		object.addModule( std::make_shared<CFlightModel>( 1.0, 0.2 ) );
		object.addModule( std::make_shared<CAffiliation>( team ) );
		object.addModule( std::make_shared<CImpactDamageSource>( 0.01, 1.0 ) );

		object.addProperty( property::CProperty::create("_type_", &object, std::string("ship")) );
		dat.addAttributes( object );
	}

	void CSpawnManager::makeBullet( const std::string& type, IGameObject& object, const IGameObject& shooter ) const
	{
		auto& dat = mDataManager->getProjectileData( type );

		object.addModule( std::make_shared<CFlightModel>( 100.0, 0.01 ) );
		object.addModule( std::make_shared<CTimedDeletion>( dat.lifetime() ) );
		auto shared = std::const_pointer_cast<IGameObjectView>(shooter.shared_from_this());
		object.addModule( std::make_shared<CAffiliation>( shared ) );
		object.addModule( std::make_shared<CImpactDamageSource>( 0.5, 0.5 ) );

		// add circular fixture
		b2CircleShape shape;
		shape.m_radius = dat.radius();
		b2FixtureDef def;
		def.density = 1.0;
		def.restitution = 0.5;
		def.shape = &shape;
		/// \todo set density for mass!
		auto fix = object.getBody()->CreateFixture( &def );
		object.getBody()->SetBullet(true);
		object.getBody()->ApplyLinearImpulseToCenter( object.getBody()->GetWorldVector(b2Vec2( dat.propellVelocity() , 0)), true );
		object.setIgnoreCollisionTarget( shooter.body() );

		object.addProperty( property::CProperty::create("_type_", &object, std::string("bullet")) );
	}
}
}

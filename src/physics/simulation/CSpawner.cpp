#include "CSpawner.h"
#include "Box2D/Box2D.h"
#include "physics/data/Fixture.h"
#include "physics/data/Body.h"

namespace physics
{
namespace simulation
{
	b2Body* CSpawner::spawnBody( b2World& world, const data::BodyDef& body ) const
	{
		b2BodyDef new_body;
		new_body.type            = b2_dynamicBody;
		new_body.position        = body.position();
		new_body.angle           = body.angle();
		new_body.linearVelocity  = body.velocity();
		new_body.angularVelocity = body.angular_velocity();
		new_body.angularDamping  = body.angularDamping();
		new_body.linearDamping   = body.linearDamping();
		new_body.bullet          = body.bullet();
		new_body.fixedRotation   = body.fixedRotation();
		
		return world.CreateBody(&new_body);
	}
	
	b2Fixture* CSpawner::spawnFixture( b2Body& target, const data::Fixture& fixture ) const
	{
		b2CircleShape  circle;
		b2PolygonShape polygon;
		
		b2FixtureDef def;
		def.density     = fixture.density();
		def.restitution = fixture.restitution();
		def.friction    = fixture.friction();
		def.isSensor    = fixture.is_sensor();
		
		if( fixture.shape().type() == typeid(data::CircleShape) )
		{
			const data::CircleShape& circle_dat = boost::get<data::CircleShape>(fixture.shape());
			circle.m_p      = circle_dat.center();
			circle.m_radius = circle_dat.radius();
			
			def.shape = &circle;
		} 
		 else 
		{
			const data::PolygonShape& polygon_dat = boost::get<data::PolygonShape>(fixture.shape());
			if(!polygon_dat.valid())
				BOOST_THROW_EXCEPTION( std::logic_error("Polygon not valid in fixture!") );
			polygon.Set( polygon_dat.vertices().data(), 
						 polygon_dat.vertices().size() );
			
			def.shape = &polygon;
		}
		
		return target.CreateFixture(&def);
	}
}
}

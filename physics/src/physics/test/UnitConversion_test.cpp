#include "physics/simulation/SUnitConverter.h"
#include "physics/data/Shape.h"
#include "physics/data/Fixture.h"
#include "physics/data/Body.h"
#include "Box2D/Box2D.h"
#include <boost/test/unit_test.hpp>
#include <iostream>

using namespace physics::simulation;

BOOST_AUTO_TEST_SUITE(UnitConverter_test)

// ---------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE( Constructor )
{
	SUnitConverter conv( 2.0 );
	
	BOOST_TEST( 2.0, conv.getMeterToBox() );
	
}

BOOST_AUTO_TEST_CASE( Constructor_Error )
{
	BOOST_CHECK_THROW(SUnitConverter conv( -1.0 ), std::logic_error);
}

BOOST_AUTO_TEST_CASE( BasicConversion )
{
	SUnitConverter conv( 2.0 );
	BOOST_TEST( conv.metersToBox(1) == 2.0 );
	BOOST_TEST( conv.boxToMeters(2) == 1.0 );
	
	b2Vec2 one = b2Vec2(1, 1);
	b2Vec2 two = b2Vec2(2, 2);
	
	BOOST_CHECK(conv.metersToBox(one) == two );
	BOOST_CHECK(conv.boxToMeters(two) == one );
}

BOOST_AUTO_TEST_CASE( ShapeConversion )
{
	physics::data::CircleShape circle( 1.0, b2Vec2(2, 3) );
	SUnitConverter conv( 3.0 );
	auto converted = conv.toBoxUnits( circle );
	BOOST_TEST( converted.radius()  == 3.0 );
	BOOST_CHECK( converted.center() == b2Vec2(6.0, 9.0) );
	
	BOOST_TEST( conv.toGameUnits(converted) == circle );
	
	
	physics::data::PolygonShape polygon{b2Vec2(1, 2), b2Vec2(2, 1), b2Vec2(0, 2)};
	auto converted_p = conv.toBoxUnits( polygon );
	BOOST_CHECK( converted_p.vertices().at(0) == b2Vec2(3, 6) );
	BOOST_CHECK( converted_p.vertices().at(1) == b2Vec2(6, 3) );
	BOOST_CHECK( converted_p.vertices().at(2) == b2Vec2(0, 6) );
	
	BOOST_TEST( conv.toGameUnits(converted_p) == polygon );
}

BOOST_AUTO_TEST_CASE( FixtureConversion )
{
	physics::data::CircleShape circle( 1.0, b2Vec2(2, 3) );
	physics::data::Fixture fixture{circle};
	fixture.setFriction(2);
	fixture.setDensity(3);
	fixture.setRestitution(0.9);
	fixture.setSensor(true);
	SUnitConverter conv( 2.0 );
	
	auto converted = conv.toBoxUnits( fixture );
	
	BOOST_TEST( fixture.friction()      == converted.friction() );
	BOOST_TEST( fixture.restitution()   == converted.restitution() );
	BOOST_TEST( fixture.density()       == converted.density() ); /// \todo until we introduce mass scaling
	BOOST_TEST( conv.toBoxUnits(circle) == boost::get<physics::data::CircleShape>(converted.shape()) );

	// backward
	BOOST_TEST( conv.toGameUnits(converted).friction() == fixture.friction() );
	BOOST_TEST( conv.toGameUnits(converted).restitution() == fixture.restitution() );
	BOOST_TEST( conv.toGameUnits(converted).density() == fixture.density() );
	BOOST_TEST( conv.toGameUnits(converted).shape() == fixture.shape() );
}

BOOST_AUTO_TEST_CASE( KinematicStateConversion )
{
	const physics::data::KinematicState state( b2Vec2(1, 2), b2Vec2(3,2), 1.5, 0.8 );
	SUnitConverter conv( 2.0 );
	
	auto converted = conv.toBoxUnits( state );
	
	BOOST_TEST( state.angle()            == converted.angle() );
	BOOST_TEST( state.angular_velocity() == converted.angular_velocity() );
	BOOST_CHECK( 2.0 * state.position()  == converted.position() );
	BOOST_CHECK( 2.0 * state.velocity()  == converted.velocity() );
	
	BOOST_TEST( conv.toGameUnits(converted).angle() == state.angle() );
	BOOST_TEST( conv.toGameUnits(converted).angular_velocity() == state.angular_velocity() );
	BOOST_CHECK( conv.toGameUnits(converted).position() == state.position() );
	BOOST_CHECK( conv.toGameUnits(converted).velocity() == state.velocity() );
}

BOOST_AUTO_TEST_CASE( BodyDefConversion )
{
	physics::data::BodyDef state( b2Vec2(1, 2), b2Vec2(3,2), 1.5, 0.8 );
	state.setAngularDamping( 1.0 );
	state.setBullet( false );
	state.setFixedRotation( true );
	state.setLinearDamping( 1.2 );
	
	SUnitConverter conv( 2.0 );
	
	auto converted = conv.toBoxUnits( state );
	
	BOOST_TEST( state.angle()            == converted.angle() );
	BOOST_TEST( state.angular_velocity() == converted.angular_velocity() );
	BOOST_CHECK( 2.0 * state.position()  == converted.position() );
	BOOST_CHECK( 2.0 * state.velocity()  == converted.velocity() );
	
	BOOST_TEST( state.linearDamping()  == converted.linearDamping() );
	BOOST_TEST( state.angularDamping() == converted.angularDamping() );
	BOOST_TEST( state.bullet()         == converted.bullet() );
	BOOST_TEST( state.fixedRotation()  == converted.fixedRotation() );
	
	BOOST_TEST( conv.toGameUnits(converted).angle() == state.angle() );
	BOOST_TEST( conv.toGameUnits(converted).angular_velocity() == state.angular_velocity() );
	BOOST_CHECK( conv.toGameUnits(converted).position() == state.position() );
	BOOST_CHECK( conv.toGameUnits(converted).velocity() == state.velocity() );
	
	BOOST_TEST( conv.toGameUnits(converted).linearDamping()  == converted.linearDamping() );
	BOOST_TEST( conv.toGameUnits(converted).angularDamping() == converted.angularDamping() );
	BOOST_TEST( conv.toGameUnits(converted).bullet()         == converted.bullet() );
	BOOST_TEST( conv.toGameUnits(converted).fixedRotation()  == converted.fixedRotation() );
}


BOOST_AUTO_TEST_SUITE_END()



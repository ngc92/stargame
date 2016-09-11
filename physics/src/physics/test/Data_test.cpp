#include "physics/data/Shape.h"
#include "physics/data/Fixture.h"
#include "physics/data/Body.h"
#include "Box2D/Box2D.h"
#include <boost/test/unit_test.hpp>

using namespace physics::data;

BOOST_AUTO_TEST_SUITE(Data_test)

// ---------------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE( CircleShape_test )

BOOST_AUTO_TEST_CASE( Constructor )
{
	CircleShape shape( 1.0 );
	BOOST_TEST( shape.radius() == 1.0 );
	BOOST_CHECK( shape.center() == b2Vec2(0, 0) );
	
	CircleShape shape2( 2.0, b2Vec2(3,5) );
	BOOST_TEST( shape2.radius() == 2.0 );
	BOOST_CHECK( shape2.center() == b2Vec2(3, 5) );
}

BOOST_AUTO_TEST_CASE( Constructor_Error )
{
	BOOST_CHECK_THROW(CircleShape shape( -1.0 ), std::logic_error);
}

BOOST_AUTO_TEST_CASE( Setters )
{
	CircleShape shape( 1.0 );
	
	shape.setRadius( 5.0 );
	shape.setCenter( b2Vec2(-5, 3) );
	BOOST_TEST( shape.radius() == 5.0 );
	BOOST_CHECK( shape.center() == b2Vec2(-5, 3) );
}
BOOST_AUTO_TEST_CASE( Setters_Error )
{
	CircleShape shape( 1.0 );
	BOOST_CHECK_THROW(shape.setRadius( -1.0 ), std::logic_error);
}

BOOST_AUTO_TEST_CASE( EqualityTest )
{
	CircleShape p1(1, b2Vec2(1, 2));
	CircleShape p2(5);
	CircleShape p3(5, b2Vec2(1, 2));
	
	BOOST_TEST( p1 == p1 );
	BOOST_TEST( p2 == p2 );
	BOOST_TEST( p3 == p3 );
	
	BOOST_TEST( !(p2 == p1) );
	BOOST_TEST( !(p2 == p3) );
	BOOST_TEST( !(p1 == p3) );
}

BOOST_AUTO_TEST_SUITE_END()

// ---------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE( PolygonShape_test )

BOOST_AUTO_TEST_CASE( Constructor )
{
	PolygonShape shape;
	BOOST_TEST( shape.getVertexCount()  == 0u );
	BOOST_TEST( shape.vertices().size() == 0u );
	
	PolygonShape shape2({{0,0}, {2,2}, {0,2}});
	BOOST_TEST( shape2.getVertexCount()  == 3u );
	BOOST_TEST( shape2.vertices().size() == 3u );
	BOOST_CHECK( shape2.vertices().at(0) == b2Vec2(0, 0) );
	BOOST_CHECK( shape2.vertices().at(1) == b2Vec2(2, 2) );
	BOOST_CHECK( shape2.vertices().at(2) == b2Vec2(0, 2) );
}

BOOST_AUTO_TEST_CASE( Constructor_Error )
{
	// too few arguments
	BOOST_CHECK_THROW(PolygonShape shape( {{0,0}} ), std::logic_error);
	BOOST_CHECK_THROW(PolygonShape shape( {{0,0}, {1, 3}} ), std::logic_error);
	
	// more values than box supports
	BOOST_CHECK_THROW(PolygonShape shape( {{0,0}, {1, 3}, {0, 4}, {1, 5}, {3,4}, {1,4}, {1,5}, {1,3}, {0,9}, {1,3}} ), std::logic_error);
}

BOOST_AUTO_TEST_CASE( Valid )
{
	PolygonShape shape;
	BOOST_TEST( shape.valid() == false );
	
	PolygonShape shape2({{0,0}, {2,2}, {0,2}});
	BOOST_TEST( shape2.valid()  == true );
}

BOOST_AUTO_TEST_CASE( Setter )
{
	PolygonShape shape;
	BOOST_TEST( shape.valid() == false );
	shape.setVertices( {{0,0}, {2,2}, {0,2}} );
	BOOST_TEST( shape.getVertexCount()  == 3u );
	BOOST_TEST( shape.vertices().size() == 3u );
	BOOST_CHECK( shape.vertices().at(0) == b2Vec2(0, 0) );
	BOOST_CHECK( shape.vertices().at(1) == b2Vec2(2, 2) );
	BOOST_CHECK( shape.vertices().at(2) == b2Vec2(0, 2) );
}

BOOST_AUTO_TEST_CASE( Setters_Error )
{
	PolygonShape shape;
	BOOST_CHECK_THROW(shape.setVertices( {{-1, 1}} ), std::logic_error);
	BOOST_CHECK_THROW(shape.setVertices( {{0,0}, {1, 3}, {0, 4}, {1, 5}, {3,4}, {1,4}, {1,5}, {1,3}, {0,9}, {1,3}} ), std::logic_error);
}

BOOST_AUTO_TEST_CASE( EqualityTest )
{
	PolygonShape p1;
	BOOST_TEST( p1 == p1 );
	
	PolygonShape p2({{0,0}, {2,2}, {0,2}});
	PolygonShape p3({{0,0}, {2,2}, {0,2}, {0, 1}});
	
	BOOST_TEST( p2 == p2 );
	BOOST_TEST( !(p2 == p1) );
	BOOST_TEST( !(p2 == p3) );
}

BOOST_AUTO_TEST_SUITE_END()

// ---------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(Fixture_test)

BOOST_AUTO_TEST_CASE( Constructor )
{
	Fixture fix{CircleShape(1)};
	
	BOOST_TEST( fix.is_sensor()  == false );
	BOOST_TEST( fix.density()    == 1.0 );
	BOOST_CHECK( fix.shape().type() == typeid(CircleShape) );
}

BOOST_AUTO_TEST_CASE( Constructor_error )
{
	BOOST_CHECK_THROW(Fixture fix{PolygonShape()}, std::logic_error);
}

BOOST_AUTO_TEST_CASE( Setters )
{
	Fixture fix{CircleShape(1)};
	fix.setDensity( 5.0 );
	fix.setRestitution( 0.5 );
	fix.setFriction( 1.6 );
	fix.setSensor(true);
	
	BOOST_TEST( 5.f  == fix.density() );
	BOOST_TEST( 0.5f == fix.restitution() );
	BOOST_TEST( 1.6f == fix.friction() );
	BOOST_TEST( fix.is_sensor() );
	
	fix.setShape( CircleShape(1) );
	BOOST_TEST( fix.shape() == Fixture::shape_t(CircleShape(1)) );
}

BOOST_AUTO_TEST_CASE( Setters_return )
{
	Fixture fix{CircleShape(1)};
	BOOST_TEST( &fix.setDensity(5) == &fix );
	BOOST_TEST( &fix.setRestitution(5) == &fix );
	BOOST_TEST( &fix.setFriction(5) == &fix );
	BOOST_TEST( &fix.setSensor(true) == &fix );
	BOOST_TEST( &fix.setShape(CircleShape(1)) == &fix );
}

BOOST_AUTO_TEST_CASE( Setters_error )
{
	Fixture fix{CircleShape(1)};
	fix.setDensity(0.5);
	fix.setRestitution( 1.6 );
	fix.setFriction( 3.2f );
	
	BOOST_CHECK_THROW( fix.setDensity(-1),           std::domain_error );	
	BOOST_CHECK_THROW( fix.setRestitution(-1),       std::domain_error );
	BOOST_CHECK_THROW( fix.setFriction(-1),          std::domain_error );
	BOOST_CHECK_THROW( fix.setShape(PolygonShape()), std::logic_error );
	
	BOOST_TEST( fix.density()     == 0.5f );
	BOOST_TEST( fix.restitution() == 1.6f );
	BOOST_TEST( fix.friction()    == 3.2f );
	BOOST_TEST( fix.shape()       == Fixture::shape_t(CircleShape(1)) );
}

BOOST_AUTO_TEST_SUITE_END()

// ---------------------------------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE( KinematicState_test )

BOOST_AUTO_TEST_CASE( Constructor )
{
	KinematicState state( b2Vec2(4, 3), b2Vec2(-4, 3), 4.3f, 1.2f );
	BOOST_CHECK( state.position() == b2Vec2(4, 3) );
	BOOST_CHECK( state.velocity() == b2Vec2(-4, 3) );
	BOOST_TEST(  state.angle()    == 4.3f );
	BOOST_TEST(  state.angular_velocity() == 1.2f );
}

BOOST_AUTO_TEST_CASE( Setters )
{
	KinematicState state( b2Vec2(0, 0) );
	
	state.setPosition( b2Vec2(4, 3) );
	state.setVelocity( b2Vec2(-4, 3) );
	state.setAngle( 4.3f );
	state.setAngularVelocity( 1.2f );
	
	BOOST_CHECK( state.position() == b2Vec2(4, 3) );
	BOOST_CHECK( state.velocity() == b2Vec2(-4, 3) );
	BOOST_TEST(  state.angle()    == 4.3f );
	BOOST_TEST(  state.angular_velocity() == 1.2f );
}


BOOST_AUTO_TEST_CASE( Setters_return )
{
	KinematicState state( b2Vec2(0, 0) );
	
	BOOST_TEST( &state = &state.setPosition( b2Vec2(0,0) ) );
	BOOST_TEST( &state = &state.setVelocity( b2Vec2(0,0) ) );
	BOOST_TEST( &state = &state.setAngle( 0 ) );
	BOOST_TEST( &state = &state.setAngularVelocity( 0 ) );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( BodyDef_test )

// we are not testing the KinematicState subobject here!

BOOST_AUTO_TEST_CASE( Constructor )
{
	BodyDef def( b2Vec2(4, 3), b2Vec2(-4, 3), 4.3f, 1.2f );
	BOOST_CHECK( def.position() == b2Vec2(4, 3) );
	BOOST_CHECK( def.velocity() == b2Vec2(-4, 3) );
	BOOST_TEST(  def.angle()    == 4.3f );
	BOOST_TEST(  def.angular_velocity() == 1.2f );
	
	BOOST_TEST(  def.linearDamping() == 0.f );
	BOOST_TEST(  def.angularDamping() == 0.f );
	BOOST_TEST(  def.fixedRotation() == false );
	BOOST_TEST(  def.bullet() == false );
}

BOOST_AUTO_TEST_CASE( Setters )
{
	BodyDef def( b2Vec2(0, 0) );
	
	def.setLinearDamping(0.7);
	def.setAngularDamping(0.2);
	def.setFixedRotation(true);
	def.setBullet(true);
	
	BOOST_TEST( def.linearDamping()  == 0.7f );
	BOOST_TEST( def.angularDamping() == 0.2f );
	BOOST_TEST( def.fixedRotation()  == true );
	BOOST_TEST( def.bullet()         == true );
}

BOOST_AUTO_TEST_CASE( Setters_return )
{
	BodyDef def( b2Vec2(0, 0) );
	
	BOOST_TEST( &def = &def.setLinearDamping( 1.f ) );
	BOOST_TEST( &def = &def.setAngularDamping( 0.8f ) );
	BOOST_TEST( &def = &def.setFixedRotation( true ) );
	BOOST_TEST( &def = &def.setBullet( false ) );
}

BOOST_AUTO_TEST_CASE( Setters_error )
{
	BodyDef def( b2Vec2(0, 0) );
	
	BOOST_CHECK_THROW( def.setLinearDamping( -0.3 ),  std::domain_error );
	BOOST_CHECK_THROW( def.setAngularDamping( -0.3 ), std::domain_error );
	
	BOOST_TEST( def.linearDamping()  == 0.0 );
	BOOST_TEST( def.angularDamping() == 0.0 );
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()


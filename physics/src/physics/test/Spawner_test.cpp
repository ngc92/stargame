#include "physics/simulation/CSpawner.h"
#include "physics/data/Fixture.h"
#include "physics/data/Body.h"
#include "Box2D/Box2D.h"
#include <boost/test/unit_test.hpp>

using namespace physics::simulation;

BOOST_AUTO_TEST_SUITE(Spawner_test)

struct SpawnFixture_fixture
{
	SpawnFixture_fixture() { body = world.CreateBody(&body_def); }
	~SpawnFixture_fixture() { }
	
	CSpawner spawner;
	b2World world = b2World( b2Vec2(0, 0) );
	b2BodyDef body_def;
	b2Body* body;
};

void check_spawn(const b2Body& body, const physics::data::BodyDef& dat)
{
	BOOST_CHECK( body.GetPosition()        == dat.position()         );
	BOOST_CHECK( body.GetLinearVelocity()  == dat.velocity()         );
	BOOST_TEST(  body.GetAngle()           == dat.angle()            );
	BOOST_TEST(  body.GetAngularVelocity() == dat.angular_velocity() );
	
	BOOST_TEST( body.IsBullet()          == dat.bullet() );
	BOOST_TEST( body.IsFixedRotation()   == dat.fixedRotation() );
	BOOST_TEST( body.GetLinearDamping()  == dat.linearDamping() );
	BOOST_TEST( body.GetAngularDamping() == dat.angularDamping() ); 
	BOOST_TEST( body.GetType() == b2_dynamicBody );
}

/// \todo data driven test case?
BOOST_FIXTURE_TEST_CASE(SpawnKineticProps, SpawnFixture_fixture)
{
	physics::data::BodyDef dat(b2Vec2(10, 5), b2Vec2(-5, 10), 5, 1.6f);
	
	b2Body* body = spawner.spawnBody(world, dat);
	BOOST_REQUIRE( body != nullptr );
	
	check_spawn(*body, dat);
	BOOST_CHECK( body->GetUserData() == nullptr );
	
	dat.setBullet(true);
	dat.setLinearDamping(0.5);
	check_spawn( *spawner.spawnBody(world, dat), dat );
	
	dat.setFixedRotation(true);
	dat.setAngularDamping(0.8);
	check_spawn( *spawner.spawnBody(world, dat), dat );
}

BOOST_FIXTURE_TEST_CASE(SpawnFixtureProps, SpawnFixture_fixture)
{
	physics::data::Fixture fix(physics::data::CircleShape(1));
	fix.setFriction(0.65);
	fix.setRestitution(0.8);
	fix.setSensor(true);
	fix.setDensity(0.6);
	
	b2Fixture* fx = spawner.spawnFixture(*body, fix);
	
	BOOST_CHECK( fx->GetDensity()     == fix.density()     );
	BOOST_CHECK( fx->GetRestitution() == fix.restitution() );
	BOOST_CHECK( fx->GetFriction()    == fix.friction()    );
	BOOST_CHECK( fx->IsSensor()       == fix.is_sensor()   );
}

BOOST_FIXTURE_TEST_CASE(SpawnFixtureShape_Circle, SpawnFixture_fixture)
{
	physics::data::Fixture fix(physics::data::CircleShape{4.f, b2Vec2(1, 5)});
	
	b2Fixture* fx = spawner.spawnFixture(*body, fix);
	
	BOOST_TEST_REQUIRE( (fx->GetShape()->GetType()) == b2Shape::e_circle );
	BOOST_CHECK( ((const b2CircleShape*)fx->GetShape())->m_radius == 4.f);
	BOOST_CHECK( ((const b2CircleShape*)fx->GetShape())->m_p      == b2Vec2(1, 5));
}

BOOST_FIXTURE_TEST_CASE(SpawnFixtureShape_Polygon, SpawnFixture_fixture)
{
	physics::data::Fixture fix(physics::data::PolygonShape({{0, 0}, {2, 2}, {0, 2}}));
	
	b2Fixture* fx = spawner.spawnFixture(*body, fix);
	
	BOOST_TEST_REQUIRE( (fx->GetShape()->GetType()) == b2Shape::e_polygon );
	BOOST_TEST_REQUIRE( ((const b2PolygonShape*)fx->GetShape())->GetVertexCount() == 3);
	
	BOOST_CHECK( ((const b2PolygonShape*)fx->GetShape())->GetVertex(0) == b2Vec2(0, 0));
	BOOST_CHECK( ((const b2PolygonShape*)fx->GetShape())->GetVertex(1) == b2Vec2(2, 2));
	BOOST_CHECK( ((const b2PolygonShape*)fx->GetShape())->GetVertex(2) == b2Vec2(0, 2));
}

BOOST_AUTO_TEST_SUITE_END()


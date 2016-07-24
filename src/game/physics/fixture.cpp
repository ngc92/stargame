#include "fixture.h"
#include "body.h"
#include "shape.h"
#include "consts.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <iostream>

namespace game
{
namespace physics
{
	Fixture::Fixture(b2Fixture& source) : mFixture(source)
	{
	}

	Fixture Fixture::create( Body& body, const Shape& shape, float density )
	{
		b2FixtureDef def;
		def.density = density;
		def.shape = as_b2shape(shape);
		return create(body, def);
	}

	Fixture Fixture::create( Body& body, b2FixtureDef def )
	{
		def.density = def.density * KILOGRAM_TO_BOX / METERS_TO_BOX / METERS_TO_BOX;
		// now, create the new shape;
		Shape shape(*def.shape);
		shape.scale( METERS_TO_BOX );
		def.shape = as_b2shape(shape);
		return *body.body()->CreateFixture(&def);
	}

	/// Get the child shape.
	Shape Fixture::getShape() const
	{
		return Shape(*mFixture.GetShape());
	}

	/// Set if this fixture is a sensor.
	Fixture& Fixture::setSensor(bool sensor)
	{
		mFixture.SetSensor( sensor );
	}

	/// Is this fixture a sensor (non-solid)?
	/// @return true if the shape is a sensor.
	bool Fixture::is_sensor() const
	{
		return mFixture.IsSensor();
	}

	/// Get the density of this fixture.
	float Fixture::density() const
	{
		return mFixture.GetDensity() * BOX_TO_KILOGRAM / BOX_TO_METERS / BOX_TO_METERS;
	}

	/// Get the coefficient of friction.
	float Fixture::friction() const
	{
		return mFixture.GetFriction();
	}

	/// Get the coefficient of restitution.
	float Fixture::restitution() const
	{
		return mFixture.GetRestitution();
	}

	/// Set the density of this fixture in kg/m²
	/// causes recalculation of the parent body's mass.
	Fixture& Fixture::setDensity( float density )
	{
		assert( density >= 0 );
		mFixture.SetDensity( density * KILOGRAM_TO_BOX / METERS_TO_BOX / METERS_TO_BOX );
		mFixture.GetBody()->ResetMassData();
		return *this;
	}

	/// Set the (dimensionless) coefficient of friction.
	Fixture& Fixture::setFriction( float friction )
	{
		assert( friction >= 0);
		mFixture.SetFriction( friction );
		return *this;
	}

	/// Set the (dimensionless) coefficient of restitution.
	Fixture& Fixture::setRestitution( float restitution )
	{
		assert( restitution >= 0);
		mFixture.SetRestitution( restitution );
		return *this;
	}

	/// changes the density of the fixture such that the mass becomes the
	/// given value (in kg)
	Fixture& Fixture::setMass( float new_mass )
	{
		// compute weight in case of unit density to get area
		b2MassData mass;
		mFixture.GetShape()->ComputeMass(&mass, 1);
		float area = mass.mass * BOX_TO_METERS * BOX_TO_METERS;
		float newdens = new_mass / area;
		setDensity( newdens );
		return *this;
	}

	/// changes the density of the fixture such that the mass changes by
	/// the given value (in kg)
	Fixture& Fixture::addMass( float addition )
	{
		b2MassData mass;
		mFixture.GetMassData(&mass);
		setMass( mass.mass + addition );

		return *this;
	}
}
}

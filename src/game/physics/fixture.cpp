#include "fixture.h"
#include "body.h"
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
	// helper functions for rescaling shapes
	/// \todo this should be solved with a variant i think.
	b2CircleShape scale( b2CircleShape source, float factor )
	{
		source.m_p *= factor;
		source.m_radius *= factor;
		return std::move(source);
	}

	b2EdgeShape scale( b2EdgeShape source, float factor )
	{
		source.m_vertex0 *= factor;
		source.m_vertex1 *= factor;
		source.m_vertex2 *= factor;
		source.m_vertex3 *= factor;
		return std::move(source);
	}

	b2PolygonShape scale( b2PolygonShape source, float factor )
	{
		std::array<b2Vec2, b2_maxPolygonVertices> vertices;
		for(int i = 0; i < source.GetVertexCount(); ++i)
		{
			vertices[i] = factor * source.GetVertex(i);
		}
		std::cout << "SCALE POLYGON\n";

		source.Set( vertices.data(), source.GetVertexCount() );
		return std::move(source);
	}

	Fixture::Fixture(b2Fixture& source) : mFixture(source)
	{
	}

	Fixture Fixture::create( Body& body, const b2Shape& shape, float density )
	{
		b2FixtureDef def;
		def.density = density;
		def.shape = &shape;
		return create(body, def);
	}

	Fixture Fixture::create( Body& body, b2FixtureDef def )
	{
		def.density = def.density * KILOGRAM_TO_BOX / METERS_TO_BOX / METERS_TO_BOX;
		// now, create the new shape;
		b2CircleShape circle;
		b2EdgeShape edge;
		b2PolygonShape polygon;
		switch(def.shape->GetType())
		{
		case b2Shape::e_circle:
			circle = scale(*(const b2CircleShape*)def.shape, METERS_TO_BOX);
			def.shape = &circle;
			break;
		case b2Shape::e_edge:
			edge = scale(*(const b2EdgeShape*)def.shape, METERS_TO_BOX);
			def.shape = &edge;
			break;
		case b2Shape::e_polygon:
			polygon = scale(*(const b2PolygonShape*)def.shape, METERS_TO_BOX);
			def.shape = &polygon;
			break;
		case b2Shape::e_chain:
			assert(0);
		}
		return *body.body()->CreateFixture(&def);
	}

	/// Get the child shape.
	const b2Shape& Fixture::shape() const
	{
		return *mFixture.GetShape();
	}

	/// Set if this fixture is a sensor.
	void Fixture::setSensor(bool sensor)
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
		shape().ComputeMass(&mass, 1);
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

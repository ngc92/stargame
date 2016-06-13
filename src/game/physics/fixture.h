#ifndef FIXTURE_H_INCLUDED
#define FIXTURE_H_INCLUDED

class b2Fixture;
class b2Shape;
class b2FixtureDef;

namespace game
{
namespace physics
{
	class Body;

	class Fixture
	{
	public:
		Fixture(b2Fixture& source);

		static Fixture create( Body&, const b2Shape&, float density );
		static Fixture create( Body&, b2FixtureDef def );

		/// Get the child shape.
		const b2Shape& shape() const;

		/// Set if this fixture is a sensor.
		void setSensor(bool sensor);

		/// Is this fixture a sensor (non-solid)?
		/// @return true if the shape is a sensor.
		bool is_sensor() const;

		/// Get the density of this fixture in kg/m²
		float density() const;
		/// Get the (dimensionless) coefficient of friction.
		float friction() const;
		/// Get the (dimensionless) coefficient of restitution.
		float restitution() const;

		/// Set the density of this fixture in kg/m²
		/// causes recalculation of the parent body's mass.
		Fixture& setDensity( float density );
		/// Set the (dimensionless) coefficient of friction.
		Fixture& setFriction( float friction );
		/// Set the (dimensionless) coefficient of restitution.
		Fixture& setRestitution( float restitution );

		// helper functions
		/// changes the density of the fixture such that the mass becomes the
		/// given value (in kg)
		Fixture& setMass( float mass );

		/// changes the density of the fixture such that the mass changes by
		/// the given value (in kg)
		Fixture& addMass( float mass );

	private:
		b2Fixture& mFixture;
	};
}
}

#endif // FIXTURE_H_INCLUDED

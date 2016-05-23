#include <Box2D/Box2D.h>
#include "physics.h"

void setFixtureMass(b2Fixture& fixture, float new_mass)
{
	b2MassData mass;
	fixture.GetShape()->ComputeMass(&mass, 1);
	float newdens = new_mass / mass.mass;
	fixture.SetDensity( newdens );
	fixture.GetBody()->ResetMassData();
}

void addMassToFixture(b2Fixture& fixture, float addition)
{
	b2MassData mass;
	fixture.GetMassData(&mass);
	setFixtureMass( fixture, mass.mass + addition );
}

#ifndef PHYSICS_H_INCLUDED
#define PHYSICS_H_INCLUDED

class b2Fixture;
class b2Body;

void setFixtureMass(b2Fixture& fixture, float new_mass);
void addMassToFixture(b2Fixture& fixture, float addition);

#endif // PHYSICS_H_INCLUDED

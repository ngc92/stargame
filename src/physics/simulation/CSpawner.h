#ifndef CSPAWNER_H_INCLUDED
#define CSPAWNER_H_INCLUDED

#include "ISpawner.h"

namespace physics
{
namespace simulation
{
	class CSpawner: public ISpawner
	{
	public:
		b2Body*    spawnBody( b2World& world,    const data::BodyDef& body ) const override;
		b2Fixture* spawnFixture( b2Body& target, const data::Fixture& fixture ) const override;
	};
}
}

#endif // CSPAWNER_H_INCLUDED

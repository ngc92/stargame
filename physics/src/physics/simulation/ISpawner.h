#ifndef ISPAWNER_H_INCLUDED
#define ISPAWNER_H_INCLUDED

class b2Body;
class b2Fixture;
class b2World;

namespace physics 
{
namespace data
{
	class Fixture;
	class BodyDef;
}

namespace simulation
{
	class ISpawner
	{
	public:
		virtual b2Body*    spawnBody( b2World& world,    const data::BodyDef& body ) const = 0;
		virtual b2Fixture* spawnFixture( b2Body& target, const data::Fixture& fixture ) const = 0;
	};
}
}

#endif // ISPAWNER_H_INCLUDED

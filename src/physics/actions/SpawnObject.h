#ifndef SPAWNOBJECT_H_INCLUDED
#define SPAWNOBJECT_H_INCLUDED

#include "Box2D/Common/b2Math.h"
#include "physics/data/Body.h"
#include "physics/data/Fixture.h"
#include <vector>

namespace physics
{
	namespace actions
	{
		struct SpawnObject
		{
			data::BodyDef body;
			std::vector<data::Fixture> fixtures;
		};
	}
}

#endif // SPAWNOBJECT_H_INCLUDED

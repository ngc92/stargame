#ifndef SPAWNEVENT_H_INCLUDED
#define SPAWNEVENT_H_INCLUDED

#include "physics/data/Body.h"

namespace physics
{
namespace events
{
	struct SpawnEvent
	{
		uint64_t uuid;
		data::KinematicState state;
	};
}
}

#endif // SPAWNEVENT_H_INCLUDED

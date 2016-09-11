#ifndef OBJECTUPDATEEVENT_H_INCLUDED
#define OBJECTUPDATEEVENT_H_INCLUDED

#include <Box2D/Common/b2Math.h>

namespace physics
{
	namespace events
	{
		struct ObjectStateUpdateEvent
		{
			uint64_t object_id;
			b2Vec2   position;
			b2Vec2   velocity;
			float    rotation;
			float    ang_velocity;
		};
	}
}

#endif // OBJECTUPDATEEVENT_H_INCLUDED

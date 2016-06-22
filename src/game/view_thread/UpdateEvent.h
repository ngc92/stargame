#ifndef UPDATEEVENT_H_INCLUDED
#define UPDATEEVENT_H_INCLUDED

#include "property/property.h"
#include "SpawnEvent.h"

namespace game
{
namespace view_thread
{
	struct UpdateEvent
	{
		uint64_t id;
        b2Vec2 position;
        b2Vec2 velocity;
        float angle;
        float angular_velocity;
	};

	struct DespawnEvent
	{

	};

    using Event = boost::variant<UpdateEvent, SpawnEvent, DespawnEvent>;
}
}

#endif // UPDATEEVENT_H_INCLUDED

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
		uint64_t id;
	};
	
	struct PropertyEvent
	{
		uint64_t id;			//!< ID of the associated game object
		std::string path;		//!< full path of the changed property
		property::data_t value;	//!< new value of the property.
	};

	using Event = boost::variant<UpdateEvent, SpawnEvent, DespawnEvent, PropertyEvent>;
}
}

#endif // UPDATEEVENT_H_INCLUDED

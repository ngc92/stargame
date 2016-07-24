#ifndef THREADSTREAMS_H_INCLUDED
#define THREADSTREAMS_H_INCLUDED

#include "UpdateEvent.h"
#include "ThreadStreamInterface.h"

namespace game
{
	namespace threading
	{
		/// this struct represents and action that can be applied to a game object.
		/// It saves a functor for the action, and the id of the object to target.
		/// \todo something like this cannot be send over network!
		struct ObjectAction
		{
			uint64_t target_id;
			std::function<void(IGameObject&)> action;
		};
		//using Action = boost::variant<std::function<void(IGameWorld&)>, ObjectAction>;
		using Action = ObjectAction;
	
		class EventStream : public ThreadStream<Event> {};
		class ActionStream : public ThreadStream<Action> {};
	}
}

#endif // THREADSTREAMS_H_INCLUDED

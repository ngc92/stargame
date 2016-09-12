#ifndef PHYSICSTHREAD_H_INCLUDED
#define PHYSICSTHREAD_H_INCLUDED

#include <vector>

namespace physics
{
	namespace events
	{
		class ObjectStateUpdateEvent;
	}
	
	namespace actions
	{
		class SpawnObject;
	}
	
	/*! \brief Main class for a physics simulation.
		\details The actual simulation is offloaded to another thread.
	*/
	class IPhysicsThread
	{
	public:
		virtual ~IPhysicsThread() = default;
		
		virtual void start() = 0;
		virtual bool is_running() const = 0;
		virtual void stop() = 0;
		
		// communication
		virtual void updateEvents() = 0;
		virtual const std::vector<events::ObjectStateUpdateEvent>& getEvents() const = 0;
		
		virtual void pushAction( actions::SpawnObject spac ) = 0;
	};
}

#endif // PHYSICSTHREAD_H_INCLUDED

#ifndef PHYSICSTHREAD_H_INCLUDED
#define PHYSICSTHREAD_H_INCLUDED

namespace physics
{
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
	};
}

#endif // PHYSICSTHREAD_H_INCLUDED

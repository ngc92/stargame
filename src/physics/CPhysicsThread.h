#ifndef CPHYSICSTHREAD_H_INCLUDED
#define CPHYSICSTHREAD_H_INCLUDED

#include "IPhysicsThread.h"
#include "core/buffered_thread_stream.h"
#include "simulation/CSimulation.h"
#include <thread>
#include <atomic>
#include <chrono>

namespace physics
{
namespace detail
{
	class CPhysicsThread: public IPhysicsThread 
	{
	public:
		CPhysicsThread();
		~CPhysicsThread();
		
		void start() override;
		bool is_running() const override;
		void stop() override;
	private:
		
		void loop();
		void step( double dt );
		
		// handler functions
		void onUpdateObject(const events::ObjectStateUpdateEvent& event);
		
		// thread management
		std::thread mSimulationThread;
		std::atomic<bool> mRunSimulation;
		std::atomic<bool> mRunThread;
		std::chrono::steady_clock::time_point mLastStep;
		
		
		// communication management
		core::BufferedThreadStream< std::vector<events::ObjectStateUpdateEvent> > mUpdateEvents;
		
		simulation::CSimulation mSimulation;
	};
}
}


#endif // CPHYSICSTHREAD_H_INCLUDED

#include "CPhysicsThread.h"
#include "simulation/ISpawner.h"

namespace physics
{
namespace detail
{
	CPhysicsThread::CPhysicsThread() : 
		mRunSimulation(false),
		mRunThread( true ), 
		mSimulation(nullptr, nullptr)
	{
		mSimulationThread = std::thread([this](){ this->loop(); });
	}
	
	CPhysicsThread::~CPhysicsThread()
	{
		mRunThread = false;
		mSimulationThread.join();
	}
	
	void CPhysicsThread::start()
	{
		mRunSimulation = true;
	}
	
	bool CPhysicsThread::is_running() const
	{
		return mRunSimulation;
	}
	
	void CPhysicsThread::stop()
	{
		mRunSimulation = false;
	}
	
	void CPhysicsThread::loop()
	{
		while(mRunThread)
		{
			auto diff = std::chrono::steady_clock::now() - mLastStep;
			mLastStep = std::chrono::steady_clock::now();
			double dt = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() / 1000.0;
			if(mRunSimulation)
				step(dt);
			std::this_thread::sleep_for( std::chrono::microseconds(1000/50) );
		}
	}
	
	void CPhysicsThread::step( double dt )
	{
		// this pushes all physics events into the queues
		mSimulation.step( dt );
		// now update the buffers atomically
		mUpdateEvents.publish();
	}
	
	void CPhysicsThread::onUpdateObject(const events::ObjectStateUpdateEvent& event)
	{
		mUpdateEvents.push( event );
	}
}
}

#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include <Box2D/Box2D.h>
#include <functional>
#include "physics/events/ObjectUpdateEvent.h"
#include "physics/actions/SpawnObject.h"
#include "ISimulation.h"

namespace physics
{
namespace simulation
{	
	class ISpawner;
	class CSimulation : public ISimulation
	{
	public:
		CSimulation(std::unique_ptr<ISpawner> spawner, std::shared_ptr<ISimulationEventListener> listener);
		~CSimulation();
		
		std::size_t getBodyCount() const override;
		
		/// perform a single simulation timestep.
		/// \param dt Passed time since last step, in seconds.
		void step( double dt /*[s]*/ );
		
		double getStepSize() const override { return mStepSize; }
		
		/// spawn an object
		void spawn( const actions::SpawnObject& spw ) override;
		
		// unit conversion interface
		double getMeterToBox() const override { return mMetersToBox; }
	private:
		
		void tick();
		
		b2World mWorld;
		double mStepSize    = 1.0/100;
		double mPartialStep = 0;
		
		// conversion factors
		double mMetersToBox = 1;
		
		std::shared_ptr<ISimulationEventListener> mListener;
		std::unique_ptr<ISpawner> mSpawner;
	};
}
}

#endif // SIMULATION_H_INCLUDED

#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "ISimulation.h"
#include <Box2D/Box2D.h>
#include <functional>
#include "SUnitConverter.h"
#include "userdata.h"
#include "physics/events/ObjectUpdateEvent.h"
#include "physics/actions/SpawnObject.h"

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
		
		const SUnitConverter& getConverter() const override { return mConverter; }
	private:
		
		void tick();
		
		b2World mWorld;
		double mStepSize    = 1.0/100;
		double mPartialStep = 0;
		
		std::vector<std::unique_ptr<BodyUserData>> mUserData;
		std::uint64_t next_id = 0;
		
		SUnitConverter mConverter;
		std::shared_ptr<ISimulationEventListener> mListener;
		std::unique_ptr<ISpawner> mSpawner;
	};
}
}

#endif // SIMULATION_H_INCLUDED

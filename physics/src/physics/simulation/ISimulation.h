#ifndef ISIMULATION_H_INCLUDED
#define ISIMULATION_H_INCLUDED

#include <cstddef>

namespace physics
{
namespace events
{
	class ObjectStateUpdateEvent;
	class SpawnEvent;
}
namespace actions
{
    class SpawnObject;
}

namespace simulation
{
    class SUnitConverter;

	struct ISimulationEventListener
	{
		virtual void onObjectStateUpdate(const events::ObjectStateUpdateEvent& event) = 0;
		virtual void onSpawn( const events::SpawnEvent& event ) = 0;
	};
	
	/*! \brief Class responsible for running the physics simulation
		\details This class runs the physics simulation itself.
				This means that it:
					* steps the Box2D world.
					* manages callbacks for physics events.
					* converts between game and Box2D units.
	*/
	class ISimulation
	{
	public:
		virtual ~ISimulation() = default;
		
		/// perform a single simulation timestep.
		/// \param dt Passed time since last step, in seconds.
		virtual void step( double dt /*[s]*/ ) = 0;
		
		virtual void spawn( const actions::SpawnObject& spw ) = 0;
		
		// info functions
		virtual std::size_t getBodyCount() const = 0;
		
		/// returns the physics step size in seconds.
		virtual double getStepSize() const = 0;
		
		
		/// gets the unit converter
		virtual const SUnitConverter& getConverter() const = 0;
	};
}
}

#endif // ISIMULATION_H_INCLUDED

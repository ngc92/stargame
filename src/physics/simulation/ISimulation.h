#ifndef ISIMULATION_H_INCLUDED
#define ISIMULATION_H_INCLUDED

namespace physics
{
namespace events
{
	class ObjectStateUpdateEvent;
	class SpawnEvent;
}
namespace simulation
{
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
		
		// unit conversion interface
		/// Gets the conversion factor from game meters to Box2D meters.
		/// This should probably be set in the constructor of the implementation class, and remain unchanged.
		virtual double getMeterToBox() const = 0;
		
		/// converts game meters to Box2D meters.
		double metersToBox(double box) const { return box * getMeterToBox(); }
		/// converts Box2D meters to game meters.
		double boxToMeters(double mks) const { return mks / getMeterToBox(); }
	};
}
}

#endif // ISIMULATION_H_INCLUDED

#ifndef LOCOMOTION_SOLVERS_H_INCLUDED
#define LOCOMOTION_SOLVERS_H_INCLUDED

#include <vector>

namespace game
{
namespace physics
{
	class Body;
}

namespace ai
{
	class Control;
	class IPropulsionSystem;
	/// \todo here we should have const IPropulsionSystem, but there does not seem to be automatic conversion to that.
	using propulsion_systems = std::vector<IPropulsionSystem*>;

	/*! \brief Calculates the controls for the propulsion systems to achieve the desired steering.
		\details takes one \p control and distributes it to the different propulsion systems, so that
			their interaction best reproduces the original intent.
		\param system The propulsion systems that are available to steer.
		\param control The desired steering.
		\param target The object to be steered.
	*/
	std::vector<Control> steer( const propulsion_systems& system, const Control& control, const physics::Body& target );
}
}

#endif // LOCOMOTION_SOLVERS_H_INCLUDED

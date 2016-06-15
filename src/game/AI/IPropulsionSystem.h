#ifndef IPROPULSIONSYSTEM_H_INCLUDED
#define IPROPULSIONSYSTEM_H_INCLUDED

class b2Vec2;

namespace game
{
namespace ai
{
	/*! \class IPropulsionSystem
		\brief Base class for anything that can move a game object around.
		\details This interface defines the communication protocol between the
				AI and anything that can be used to accelerate/rotate the object.

				For that, it provides a set of info functions describing its capabilities,
				and action functions which try to implement the control commands as
				faithfully as possible (note that this might not always be the case, e.g.
				a fixed engine can only accelerate in one direction.)

		\todo	Add interface for booster-like objects.
		\todo 	Get direction dependent thrust.
	*/
	class IPropulsionSystem
	{
	public:
		~IPropulsionSystem() = default;

		// info functions
		/// gets the maximum torque this propulsion system can produce.
		virtual float getMaxTorque() const = 0;
		/// gets the maximum thrust this propulsion system can produce.
		virtual float getMaxThrust() const = 0;

		/// calculates, how much torque would actually be generated, if
		/// the system tried to generate \p rot.
		virtual float check_rotate( float rot ) const = 0;

		/// calculates, how much thrust would actually be generated, if
		/// the system tried to generate \p thrust.
		virtual b2Vec2 check_thrust( const b2Vec2& thrust ) const = 0;

		// action functions
		/// tries to apply torque \p rot.
		virtual void rotate(float rot) = 0;
		/// tries to apply thrust \p thr.
		virtual void thrust(const b2Vec2& thr) = 0;
	};
}
}
#endif // IPROPULSIONSYSTEM_H_INCLUDED

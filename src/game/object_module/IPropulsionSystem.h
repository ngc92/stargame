#ifndef IPROPULSIONSYSTEM_H_INCLUDED
#define IPROPULSIONSYSTEM_H_INCLUDED

class b2Vec2;

namespace game
{
	/*! \class IPropulsionSystem
		\brief Base class for anything that can move a game object around
	*/
	class IPropulsionSystem
	{
	public:
		~IPropulsionSystem() = default;

		// info functions
		virtual float getMaxTorque() const = 0;
		virtual float getMaxThrust() const = 0;
		virtual float check_rotate( float rot ) const = 0;
		virtual b2Vec2 check_thrust( const b2Vec2& thrust ) const = 0;

		// action functions
		virtual void rotate(float rot) = 0;
		virtual void thrust(const b2Vec2& thr) = 0;
	};
}

#endif // IPROPULSIONSYSTEM_H_INCLUDED

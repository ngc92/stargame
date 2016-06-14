#ifndef IFLIGHTMODEL_H_INCLUDED
#define IFLIGHTMODEL_H_INCLUDED

#include "common_includes.h"

namespace game
{
	class IFlightModel : public IGameObjectModule
	{
	public:
		// physics functions
		/// change the physical state of the object to accelerate with force thrust_vector
		virtual void thrust( b2Vec2 thrust_vector ) = 0;
		/// change the physical state of the object to turn with \p torque,
		virtual void rotate( float torque )   = 0;

		virtual float getTerminalVelocity( float thrust ) = 0;
	};
}

#endif // IFLIGHTMODEL_H_INCLUDED

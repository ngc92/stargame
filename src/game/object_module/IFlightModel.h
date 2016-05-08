#ifndef IFLIGHTMODEL_H_INCLUDED
#define IFLIGHTMODEL_H_INCLUDED

#include "common_includes.h"

namespace game
{
	class IFlightModel : public IGameObjectModule
	{
	public:
		virtual void thrust( b2Vec2 thrust_vector ) = 0;
		virtual void rotate( float turn_impulse )   = 0;
	};
}

#endif // IFLIGHTMODEL_H_INCLUDED

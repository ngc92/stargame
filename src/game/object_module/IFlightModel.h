#ifndef IFLIGHTMODEL_H_INCLUDED
#define IFLIGHTMODEL_H_INCLUDED

#include "common_includes.h"
#include <boost/optional.hpp>

namespace game
{
	struct SFlightState
	{
		boost::optional<b2Vec2> position;
		boost::optional<b2Vec2> velocity;
		boost::optional<float> rotation;
	};
	
	class IFlightModel : public IGameObjectModule
	{
	public:
		virtual void thrust( b2Vec2 thrust_vector ) = 0;
		virtual void rotate( float turn_impulse )   = 0;
		
		// auto pilot functions
//		virtual void pilot( const IGameObject& ship, const SFlightState& target_state ) = 0;
	};
}

#endif // IFLIGHTMODEL_H_INCLUDED

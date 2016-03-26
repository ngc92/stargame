#ifndef FLIGHTMODEL_H_INCLUDED
#define FLIGHTMODEL_H_INCLUDED

#include "util.h"

namespace game
{
	class FlightModel
	{
	public:
		FlightModel();

		void init( b2Body& ship );
		void update_movement( b2Body& ship );

		void thrust( b2Vec2 thrust_vector );
		void rotate( float turn_impulse );
	private:
		// cached commands
		b2Vec2 mTotalThrust;
		float mTotalAngImp;

		// flight model properties
		float mOperatingSpeed;
		float mDragFactor;
	};
}

#endif // FLIGHTMODEL_H_INCLUDED

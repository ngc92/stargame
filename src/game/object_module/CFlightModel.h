#ifndef FLIGHTMODEL_H_INCLUDED
#define FLIGHTMODEL_H_INCLUDED

#include "util.h"
#include "IFlightModel.h"

namespace game
{
	class CFlightModel : public IFlightModel, public property::CPropertyObject
	{
	public:
		CFlightModel();

		// Module functions
		void onStep( IGameObject& object ) override;
		void onInit( IGameObject& object ) override;


		void update_movement( b2Body& ship );

		void thrust( b2Vec2 thrust_vector );
		void rotate( float turn_impulse );
	private:
		// flight model properties
		float mOperatingSpeed;
		float mDragFactor;

		// cached commands
		b2Vec2 mTotalThrust;
		float mTotalAngImp = 0;
	};
}

#endif // FLIGHTMODEL_H_INCLUDED

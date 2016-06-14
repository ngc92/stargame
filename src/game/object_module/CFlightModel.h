#ifndef FLIGHTMODEL_H_INCLUDED
#define FLIGHTMODEL_H_INCLUDED

#include "util.h"
#include "IFlightModel.h"

namespace game
{
	class CFlightModel : public IFlightModel, public property::CPropertyObject
	{
	public:
		CFlightModel( float op_speed, float drag_factor );

		// Module functions
		void onStep( IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action) override;
		void onInit( IGameObject& object, IGameWorld& world ) override;


		void update_movement( Body& ship );

		void thrust( b2Vec2 thrust_vector ) override;
		void rotate( float turn_impulse ) override;

		// info functions
		float getTerminalVelocity( float thrust ) override;

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

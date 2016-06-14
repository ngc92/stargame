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

		void steer( b2Vec2 desired_linear_accel, float desired_angular_accel ) override;

		// info functions
		float getTerminalVelocity( float thrust );

		void pilot( const IGameObject& ship, const SFlightState& target_state );// override;
	private:
		void registerPropulsionSystem_( IPropulsionSystem& propsys ) override;
		void removePropulsionSystem_( IPropulsionSystem& propsys ) override;

		// flight model properties
		float mOperatingSpeed;
		float mDragFactor;

		// cached commands
		b2Vec2 mTotalThrust;
		float mTotalAngImp = 0;

		bool mIsSteering = false;
		b2Vec2 mSteerVec;
		float mSteerRot;

		std::vector<IPropulsionSystem*> mPropulsionSystems;
	};
}

#endif // FLIGHTMODEL_H_INCLUDED

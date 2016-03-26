#include "FlightModel.h"
#include <Box2D/Dynamics/b2Body.h>

namespace game
{
	FlightModel::FlightModel() : mOperatingSpeed(1), mDragFactor(0.1)
	{

	}

	void FlightModel::init( b2Body& ship )
	{
		ship.SetLinearDamping( 0.0 );
		ship.SetAngularDamping( 1 );
	}

	void FlightModel::update_movement( b2Body& ship )
	{
		/// \todo this is copied from the old flight model.
		/// need sth new here.
		b2Vec2 v = ship.GetLocalVector( ship.GetLinearVelocity() );
		if( v.y < 0 )
			v.y = std::min(0.f, v.y + mOperatingSpeed);

		// decompose
		float f = -v.LengthSquared() * mDragFactor;
		v.Normalize();
		v *= f * ship.GetMass();
		ship.ApplyForceToCenter( ship.GetWorldVector(v) );

		ship.ApplyLinearImpulse( ship.GetWorldVector( mTotalThrust ) , ship.GetWorldCenter() );
		ship.ApplyAngularImpulse( mTotalAngImp * ship.GetInertia() );

		mTotalThrust = b2Vec2_zero;
		mTotalAngImp = 0;
	}

	void FlightModel::thrust( b2Vec2 thrust_vector )
	{
		mTotalThrust += thrust_vector;
	}

	void FlightModel::rotate( float turn_impulse )
	{
		mTotalAngImp += turn_impulse;
	}
}

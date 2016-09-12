#include "CFlightModel.h"
#include "IPropulsionSystem.h"
#include "consts.h"
#include "game/physics/body.h"
#include "game/physics/convert.h"
#include <boost/throw_exception.hpp>
#include <algorithm>
#include <iostream>

namespace game
{
	CFlightModel::CFlightModel( float op_speed, float drag_factor ) : CPropertyObject("flight_model"),
								 mOperatingSpeed( op_speed ),
								 mDragFactor( drag_factor ),
								 mTotalThrust( b2Vec2_zero ),
								 mTotalAngImp( 0 )
	{
	}

	void CFlightModel::onInit( IGameObject& object, IGameWorld& world )
	{
	}

	void CFlightModel::update_movement( IGameObject& ship )
	{
		/// \todo this is copied from the old flight model.
		/// need sth new here.
/*		b2Vec2 v = game::physics::local_vector(ship, ship.velocity() );
		v.x = std::max(0.f, v.x - mOperatingSpeed);

		// decompose
		float f = -v.LengthSquared() * mDragFactor;
		if( f > 0 )
			v.Normalize();
		v *= f;

		ship.applyForce( game::physics::world_vector( ship, mTotalThrust + v ) );
		ship.applyTorque( mTotalAngImp );

		mTotalThrust = b2Vec2_zero;
		mTotalAngImp = 0;
*/
		/// \todo this needs to be reworked!
	}

	void CFlightModel::onStep( IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action)
	{
		update_movement( object );
	}

	void CFlightModel::thrust( b2Vec2 thrust_vector )
	{
		mTotalThrust += thrust_vector;
	}

	void CFlightModel::rotate( float turn_impulse )
	{
		mTotalAngImp += turn_impulse;
	}

	void CFlightModel::registerPropulsionSystem_( IPropulsionSystem& propsys )
	{
		mPropulsionSystems.push_back( &propsys );
	}

	void CFlightModel::removePropulsionSystem_( IPropulsionSystem& propsys )
	{
		auto found = std::find(begin(mPropulsionSystems), end(mPropulsionSystems), &propsys);
		if(found != end(mPropulsionSystems))
			mPropulsionSystems.erase( found );
	}

	float CFlightModel::getTerminalVelocity( float thrust )
	{
		/// \todo this currently ignores the operation speed
		return std::sqrt(thrust / mDragFactor);
	}
}

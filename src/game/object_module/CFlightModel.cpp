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
	CFlightModel::CFlightModel( float op_speed, float drag_factor ) :
		CPropertyObject("flight_model"),
		 mOperatingSpeed( op_speed ),
		 mDragFactor( drag_factor ),
		 mTotalThrust( b2Vec2_zero ),
		 mTotalAngImp( 0 )
	{
	}

	void CFlightModel::onInit( IGameObject& object, IGameWorld& world )
	{
		auto& ship = object.getBody();
		if(!ship)
			BOOST_THROW_EXCEPTION( std::runtime_error("flight model module applied to bodyless game object!") );
		ship.setLinearDamping( 0.0 );
		ship.setAngularDamping( 1 );
	}

	void CFlightModel::update_movement( Body& ship )
	{
		/// \todo this is copied from the old flight model.
		/// need sth new here.
		b2Vec2 v = local_vector(ship, ship.velocity() );
		v.x = std::max(0.f, v.x - mOperatingSpeed);

		// decompose
		float f = -v.LengthSquared() * mDragFactor;
		if( f > 0 )
			v.Normalize();
		v *= f;

		ship.applyForce( world_vector( ship, mTotalThrust + v ) );
		ship.applyTorque( mTotalAngImp );

		mTotalThrust = b2Vec2_zero;
		mTotalAngImp = 0;
	}

	void CFlightModel::onStep( IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action)
	{
		Body& body = object.getBody();
		if(!body)
			BOOST_THROW_EXCEPTION( std::runtime_error("flight model module applied to bodyless game object!") );

		update_movement( body );
	}

	void CFlightModel::thrust( b2Vec2 thrust_vector )
	{
		mTotalThrust += thrust_vector;
	}

	void CFlightModel::rotate( float turn_impulse )
	{
		mTotalAngImp += turn_impulse;
	}

	float CFlightModel::getTerminalVelocity( float thrust )
	{
		/// \todo this currently ignores the operation speed
		return std::sqrt(thrust / mDragFactor);
	}
}

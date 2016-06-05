#include "CFlightModel.h"
#include <Box2D/Dynamics/b2Body.h>
#include <boost/throw_exception.hpp>
#include <iostream>

namespace game
{
	CFlightModel::CFlightModel( float op_speed ) : CPropertyObject("flight_model"),
								 mOperatingSpeed( op_speed ),
								 mDragFactor( 0.01 ),
								 mTotalThrust( b2Vec2_zero ),
								 mTotalAngImp( 0 )
	{
	}

	void CFlightModel::onInit( IGameObject& object, IGameWorld& world )
	{
		auto ship = object.getBody();
		if(!ship)
			BOOST_THROW_EXCEPTION( std::runtime_error("flight model module applied to bodyless game object!") );
		ship->SetLinearDamping( 0.0 );
		ship->SetAngularDamping( 1 );
	}

	void CFlightModel::update_movement( b2Body& ship )
	{
		/// \todo this is copied from the old flight model.
		/// need sth new here.
		b2Vec2 v = ship.GetLocalVector( ship.GetLinearVelocity() );
		v.x = std::max(0.f, v.x - mOperatingSpeed);


		// decompose
		float f = -v.LengthSquared() * mDragFactor;
		v.Normalize();
		v *= f * ship.GetMass();
		ship.ApplyForceToCenter( ship.GetWorldVector(v), true );

		ship.ApplyLinearImpulse( ship.GetWorldVector( mTotalThrust ) , ship.GetWorldCenter(), true );
		ship.ApplyAngularImpulse( mTotalAngImp * ship.GetInertia(), true );

		mTotalThrust = b2Vec2_zero;
		mTotalAngImp = 0;
	}

	void CFlightModel::onStep( IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action)
	{
		auto body = object.getBody();
		if(!body)
			BOOST_THROW_EXCEPTION( std::runtime_error("flight model module applied to bodyless game object!") );
		update_movement( *body );
	}

	void CFlightModel::thrust( b2Vec2 thrust_vector )
	{
		mTotalThrust += thrust_vector;
	}

	void CFlightModel::rotate( float turn_impulse )
	{
		mTotalAngImp += turn_impulse;
	}
/*	
	void CFlightModel::pilot( const IGameObject& ship, const SFlightState& target_state )
	{
		auto cur_pos = ship.position();
		auto cur_vel = ship.velocity();
		auto cur_ang = ship.angle();
		
		auto position_distance = target_state.position.get_value_or( cur_pos ) - cur_pos;
		/// \todo for now, this is the most simple implementation that only works for position constraints
		
		//auto velocity_distance = target_state.velocity.get_value_or( cur_vel ) - cur_vel;
	}
*/
}

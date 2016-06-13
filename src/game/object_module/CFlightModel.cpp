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
		// pilot to target
		SFlightState test_target;
		test_target.position = b2Vec2(200, 200);
		//pilot(object, test_target);

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

	void CFlightModel::pilot( const IGameObject& ship, const SFlightState& target_state )
	{
		///! \note this code is not finished!
		auto cur_pos = ship.position();
		auto cur_vel = ship.velocity();
		auto cur_ang = ship.angle();
 		auto& body = ship.body();

		if(!target_state.position)
			return;

		// gather info
		float max_thrust = 0;
		for(auto& ps : mPropulsionSystems)
		{
			max_thrust += ps->getMaxThrust();
		}
		float max_ang_acc = 0;
		for(auto& ps : mPropulsionSystems)
		{
			max_ang_acc += ps->getMaxTorque() / body.inertia();
		}

		auto distance = target_state.position.get_value_or( cur_pos ) - cur_pos;
		/// \todo for now, this is the most simple implementation that only works for position constraints
		float max_vel = getTerminalVelocity(max_thrust);
		float time_to = distance.Length() / max_vel;
		std::cout << max_vel << " " << cur_vel.Length() << "\n";
		b2Vec2 future_pos = cur_pos + time_to * cur_vel;
		auto future_distance = target_state.position.get_value_or( cur_pos ) - future_pos;

		for(auto& ps : mPropulsionSystems)
		{
			ps->thrust(local_vector(ship.body(), future_distance));
		}

		float target_angle = target_state.rotation.get_value_or( cur_ang );

		// if we are free to rotate
		if(!target_state.rotation)
			target_angle = std::atan2( future_distance.y, future_distance.x );

		float ang_dif = std::remainder(target_angle - cur_ang, 4*std::acos(0));
        float time_to_angle = ang_dif / ship.angular_velocity();
        float time_to_brake = std::abs(ship.angular_velocity() / max_ang_acc);
        float target_rotate = ang_dif;
		if(time_to_angle < time_to_brake)
			target_rotate = -ship.angular_velocity();

        // want velocity = 0 at time_to_angle
		std::cout << target_rotate << "\n";
		for(auto& ps : mPropulsionSystems)
		{
			ps->rotate(target_rotate * body.inertia());
		}


	}
}

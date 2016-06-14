#include "CFlightModel.h"
#include "IPropulsionSystem.h"
#include "consts.h"
#include "game/physics/body.h"
#include "game/physics/convert.h"
#include <boost/throw_exception.hpp>
#include <algorithm>
#include <iostream>

#include "game/ai/locomotion_control.h"
#include "game/ai/locomotion_solvers.h"

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
		test_target.position = b2Vec2(500, 500);
		pilot(object, test_target);

		// update steering
		if(mIsSteering)
		{
			ai::Control ctrl( mSteerVec, mSteerRot, 0.f );
			auto steering = ai::steer(mPropulsionSystems, ctrl, body);
			for(unsigned i = 0; i < steering.size(); ++i )
			{
				mPropulsionSystems[i]->thrust( steering[i].steer.get() );
				mPropulsionSystems[i]->rotate( steering[i].rotate.get() );
			}
			mIsSteering = false;
		}

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

	void CFlightModel::steer( b2Vec2 desired_linear_accel, float desired_angular_accel )
	{
		mIsSteering = true;
		mSteerVec = desired_linear_accel;
		mSteerRot = desired_angular_accel;
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

		/// \todo for now, this is the most simple implementation that only works for position constraints
		float max_vel = getTerminalVelocity(max_thrust);
		auto steer_vec = ai::steer_to_position(cur_pos, target_state.position.get(), cur_vel, max_thrust / body.mass(), max_vel).steer.get();

		float target_angle = std::atan2( steer_vec.y, steer_vec.x );
		float target_rotate = ai::rotate_to_angle(cur_ang, target_angle, ship.angular_velocity(), max_ang_acc).rotate.get();

		steer( steer_vec, target_rotate );

	}
}

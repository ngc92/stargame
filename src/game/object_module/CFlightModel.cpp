#include "CFlightModel.h"
#include <Box2D/Dynamics/b2Body.h>
#include <boost/throw_exception.hpp>
#include <iostream>

namespace game
{
	CFlightModel::CFlightModel() : CPropertyObject("flight_model"),
								 mOperatingSpeed(1),
								 mDragFactor(0.1),
								 mTotalThrust( b2Vec2_zero ),
								 mTotalAngImp( 0 )
	{
	}

	void CFlightModel::onInit( IGameObject& object )
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

		std::cout <<ship.GetAngle() << "\n";
	}

	void CFlightModel::onStep( IGameObject& object )
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
}

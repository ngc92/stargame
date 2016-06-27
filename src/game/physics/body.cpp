#include "body.h"
#include "consts.h"
#include <cassert>
#include <iostream>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>

namespace game
{
	Body::Body(b2Body* source) : mBody(source)
	{
	}

	Body::~Body()
	{
		destroy();
	}

	// general physics properties getters
	/// gets the current position.
	b2Vec2 Body::position() const
	{
		return BOX_TO_METERS * mBody->GetPosition();
	}

	/// gets the current rotation angle.
	float Body::angle() const
	{
		return mBody->GetAngle();
	}

	/// gets the current velocity.
	b2Vec2 Body::velocity() const
	{
		return BOX_TO_METERS * mBody->GetLinearVelocity();
	}

	/// gets the velocity of a point inside the body's frame of reference.
	b2Vec2 Body::velocity_at( const b2Vec2& local_point ) const
	{
		return BOX_TO_METERS * mBody->GetLinearVelocityFromLocalPoint( local_point );
	}

	/// gets the current angular velocity.
	float Body::angular_velocity() const
	{
		return mBody->GetAngularVelocity();
	}

	/// sets the position.
	/// \note \p new_pos in world coordinates, in game units.
	void Body::setPosition( b2Vec2 new_pos )
	{
		new_pos *= METERS_TO_BOX;
		mBody->SetTransform(new_pos, mBody->GetAngle() );
	}

	/// sets the linear velocity.
	/// \note \p new_vel in world coordinates, in game units.
	void Body::setVelocity( b2Vec2 new_vel )
	{
		new_vel *= METERS_TO_BOX;
		new_vel -= mBody->GetLinearVelocity();
		mBody->ApplyLinearImpulseToCenter( mBody->GetMass() * new_vel, true );
	}

	/// sets the angle
	void Body::setAngle( float angle )
	{
		mBody->SetTransform( mBody->GetPosition(), angle );
	}

	/// sets the angular velocity
	void Body::setAngularVelocity( float ang_vel )
	{
		ang_vel -= mBody->GetAngularVelocity();
		mBody->ApplyTorque( mBody->GetInertia() * ang_vel, true );
	}

	/// Get the linear damping of the body.
	float Body::getLinearDamping() const
	{
		assert( mBody );
		return mBody->GetLinearDamping();
	}

	/// Set the linear damping of the body.
	Body& Body::setLinearDamping(float linearDamping)
	{
		// ODE: dv/dt + c * v = 0 => m/s^2 = [c] m/s => [c] = 1/s
		assert( mBody );
		mBody->SetLinearDamping( linearDamping );
		return *this;
	}

	/// Get the angular damping of the body.
	float Body::getAngularDamping() const
	{
		assert( mBody );
		return mBody->GetAngularDamping();
	}

	/// Set the angular damping of the body.
	Body& Body::setAngularDamping(float angularDamping)
	{
		assert( mBody );
		mBody->SetAngularDamping( angularDamping );
		return *this;
	}

	/// sets the user pointer
	Body& Body::setUserPointer( void* ptr )
	{
		assert( mBody );
		mBody->SetUserData( ptr );
		return *this;
	}

	/// gets mass in kg
	float Body::mass() const
	{
		return mBody->GetMass();
	}

	/// gets the moment of inertia in kg m²
	float Body::inertia() const
	{
		return mBody->GetInertia() * BOX_TO_KILOGRAM * BOX_TO_METERS * BOX_TO_METERS;
	}

	void Body::destroy()
	{
		if(mBody) mBody->GetWorld()->DestroyBody(mBody);
		mBody = nullptr;
	}

	// dynamics
	void Body::applyForce(b2Vec2 force)
	{
		assert(mBody);
		mBody->ApplyForce( NEWTON_TO_BOX * force, mBody->GetWorldCenter(), true );
	}

	void Body::applyTorque( float torque )
	{
		assert(mBody);
		mBody->ApplyTorque( NEWTON_TO_BOX * METERS_TO_BOX * torque, true );
	}

	void Body::addLinearVelocity( b2Vec2 velocity )
	{
		assert(mBody);
		// we do not need to scale the time, as box 1s == game 1s
		// also do not convert mass, because we get value in box system, and reuse it directly.
		mBody->ApplyLinearImpulseToCenter( (METERS_TO_BOX * mBody->GetMass()) * velocity, true );
	}


}

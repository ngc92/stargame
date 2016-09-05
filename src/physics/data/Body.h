#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include "Box2D/Common/b2Math.h"

namespace physics
{
namespace data
{
	class KinematicState
	{
	public:
		KinematicState(const b2Vec2& pos, const b2Vec2& vel = b2Vec2(0, 0), float ang = 0, float ang_vel = 0):
			mPosition( pos ), mVelocity( vel ),
			mAngle( ang ), mAngularVelocity( ang_vel )
		{
		}
		
		// setters
		KinematicState& setAngle(float a) 			 { mAngle = a; 			 return *this; }
		KinematicState& setAngularVelocity(float a)  { mAngularVelocity = a; return *this; }
		KinematicState& setPosition(const b2Vec2& p) { mPosition = p; 		 return *this; }
		KinematicState& setVelocity(const b2Vec2& v) { mVelocity = v; 		 return *this; }
		
		// getters
		float angle() const 			{ return mAngle; }
		float angular_velocity() const 	{ return mAngularVelocity; }
		const b2Vec2& position() const  { return mPosition; }
		const b2Vec2& velocity() const  { return mVelocity; } 
	
	private:
		b2Vec2 mPosition;
		b2Vec2 mVelocity;

		float mAngle;
		float mAngularVelocity;
	};
	
	class BodyDef : public KinematicState
	{
	public:
		using KinematicState::KinematicState;
		
		BodyDef& setLinearDamping(  float d );
		BodyDef& setAngularDamping( float d );
		BodyDef& setFixedRotation( bool f );
		BodyDef& setBullet( bool b );
		
		float linearDamping()  const { return mLinearDamping;  }
		float angularDamping() const { return mAngularDamping; }
		bool  fixedRotation()  const { return mFixedRotation;  }
		bool  bullet()         const { return mBullet;}
		
	private:
		float mLinearDamping  = 0.f;
		float mAngularDamping = 0.f;
		
		bool mFixedRotation   = false;
		bool mBullet          = false;
		/// \todo b2BodyDef has a few more parameters, do we want them?
	};
}
}

#endif // BODY_H_INCLUDED

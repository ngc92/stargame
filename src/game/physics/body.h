#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

class b2Body;
class b2Vec2;
class b2Transform;

namespace game
{
namespace physics
{
	class Body
	{
	public:
		Body(b2Body* source);
		~Body();
		
		Body(Body&&) = default;
		Body& operator=(Body&&) = default;
		Body(const Body&) = delete;
		Body& operator=(const Body&) = delete;

		// general physics properties getters
		/// gets the current position.
		b2Vec2 position() const;
		/// gets the current rotation angle.
		float angle() const;
		/// gets the current velocity.
		b2Vec2 velocity() const;
		/// gets the velocity of a point inside the body's frame of reference.
		b2Vec2 velocity_at( const b2Vec2& local_point ) const;
		/// gets the current angular velocity.
		float angular_velocity() const;
		/// gets mass in kg
		float mass() const;
		/// gets the moment of inertia in kg m²
		float inertia() const;
		
		/*! gets the transform of the body. 
			\attention This function returns a direct reference 
						to the targets transform. It is not converted
						into game units, and only intended to be used
						as argument to other Box2D functions.
		*/
		const b2Transform& getTransform() const;

		// physics state setters
		/// sets the position.
		/// \note \p new_pos in world coordinates, in game units.
		void setPosition( b2Vec2 new_pos );

		/// sets the linear velocity.
		/// \note \p new_vel in world coordinates, in game units.
		void setVelocity( b2Vec2 new_vel );

		/// sets the angle (radians)
		void setAngle( float angle );

		/// sets the angular velocity
		void setAngularVelocity( float ang_vel );

		// other body properties
		/// Get the linear damping of the body.
		float getLinearDamping() const;
		/// Set the linear damping of the body.
		Body& setLinearDamping(float linearDamping);
		/// Get the angular damping of the body.
		float getAngularDamping() const;
		/// Set the angular damping of the body.
		Body& setAngularDamping(float angularDamping);

		/// sets the user pointer
		Body& setUserPointer( void* ptr );

		/// delete the pointed to body and remove from its world.
		/// This operation is safe to call even if mBody == nullptr
		void destroy();

		// -------------------------------------------------
		// influence body. units for parameters in SI system.
		void applyForce( b2Vec2 force );
		void applyTorque( float torque );
		void addLinearVelocity( b2Vec2 velocity );


		// conversion operator to check if a body is present
		operator bool() const { return mBody; }

		// access the full box2d body.
		b2Body* body() { return mBody; };
		const b2Body* body() const { return mBody; };
	private:
		b2Body* mBody;
	};
}
using physics::Body;
}

#endif // BODY_H_INCLUDED

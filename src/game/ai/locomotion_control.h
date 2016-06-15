#ifndef LOCOMOTION_H_INCLUDED
#define LOCOMOTION_H_INCLUDED

#include <boost/optional.hpp>
#include <Box2D/Common/b2Math.h>

namespace game
{

namespace ai
{
	/*! \brief Structure that contains calculated control variables.
		\details This includes the actual steering, as well as a time estimate
			when the respective goal will be met.
			The steering variables are boost::optional, to allow to indicate that
			not necessarly both are required.
			Objects of this type are used as output from low level steering methods.
	*/
	struct Control
	{
		Control( float rot_, float time_ ) : rotate(rot_), time(time_) {}
		Control( b2Vec2 steer_, float time_ ) : steer( std::move(steer_) ), time(time_) {}
		Control( b2Vec2 steer_, float rot_, float time_ ) : steer( std::move(steer_) ), rotate(rot_), time(time_) {}
		/// desired acceleration vector.
		boost::optional<b2Vec2> steer;
		/// desired angular acceleration.
		boost::optional<float> rotate;
		/// time estimate.
		float time;
	};

	// here comes a collection of functions that are helpful for locomotion ai

	/*! \brief rotate to target angle.
		\details calculates control value for rotating from angle \p start to the angle \p target_angle.
				This is the most basic rotation function, upon which all the other convenience functions are implemented.
		\param start Starting angle.
		\param target Target angle.
		\param vel Current angular velocity.
		\param max_accel Maximum angular acceleration.
		\return optimal angular acceleration.
	*/
	Control rotate_to_angle( float start, float target, float vel, float max_accel );


	/*! \brief steer towards a target using a simple algorithm.
		\details calculates the steering vector to get to the desired target under the assumption
				that we can directly accelerate in every direction.
		\param start Starting position.
		\param target Target position.
		\param vel Starting velocity.
		\param max_accel Maximum acceleration, assume that it can be applied into all directions.
		\param max_vel Maximum velocity (due to "air drag")
		\return The acceleration that is "optimal" to go from start to target.
	*/
	Control steer_to_position( const b2Vec2& start, const b2Vec2& target, const b2Vec2& vel, float max_accel, float max_vel );


	/*! \brief ensure constant magnitude of velocity.
		\details calculate the acceleration needed to ensure that the magnitude of the velocity reaches a desired value.
		\param vel Current velocity.
		\param target_speed Speed to be achieved.
		\param max_accel Maximum acceleration, assumed to be applicable in any direction.
	*/
	Control cruise_control( const b2Vec2& vel, float target_speed, float max_accel );

	/*! \brief ensure constant velocity.
		\details calculate the acceleration needed to ensure that the velocity reaches a desired value.
		\param vel Current velocity.
		\param target_vel Target velocity.
		\param max_accel Maximum acceleration, assumed to be applicable in any direction.
	*/
	Control cruise_control( const b2Vec2& vel, const b2Vec2& target_vel, float max_accel );
}
}

#endif // LOCOMOTION_H_INCLUDED

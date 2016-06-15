#include "locomotion_control.h"
#include <Box2D/Common/b2Math.h>
#include "util/io.h"
#include <cmath>
#include <iostream>

namespace game
{
namespace ai
{
	Control rotate_to_angle( float start, float target, float vel, float max_accel )
	{
		/*! the algorithm works a follows:
			first, check how long we need to brake to stop our rotation, and how far we come
			by that. Then either start braking, or continue accelerating.
		*/
		float ang_dif = std::remainder(target - start, 4*std::acos(0));

		float brake_dir = vel > 0 ? - max_accel : max_accel;

		// estimate braking
		float time_to_brake = -vel / brake_dir;
		float rot_by_time = brake_dir/2 * time_to_brake * time_to_brake + vel * time_to_brake;

		// if current movement direction is contrary to target rotation, change rotation.
		/// \todo if we rotate really fast, it might be better to go the other way round.
		if(ang_dif * vel < 0)
		{
			// how long do we need after braking
			Control future = rotate_to_angle(rot_by_time, target, 0, max_accel);
			return Control(brake_dir, time_to_brake + future.time);
		}

		float future_difference = std::abs(ang_dif) - std::abs(rot_by_time);

		// if we overshoot, brake, otherwise accelerate
		if( future_difference < 0 )
		{
			// here, we just have to brake
			return Control(brake_dir, time_to_brake);
		} else
		{
			// here, we have to first rotate to the target and then brake.
			// just as a crude approximation here, estimate the additional time
			// by assuming constant acceleration:
			// future_difference = a/2 t^2
			return Control(-brake_dir, time_to_brake + std::sqrt(2 * future_difference / max_accel));
		}
	}

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	Control steer_to_position( const b2Vec2& start, const b2Vec2& target, const b2Vec2& vel, float max_accel, float max_vel )
	{
		b2Vec2 distance = target - start;

		// estimate where we will be by the time we could optimally reach the target
		float time_to = distance.Length() / max_vel;
		b2Vec2 future_pos = start + time_to * vel;

		// update distance to reflect that.
		distance = target - future_pos;

		// normalize steering vector
		distance.Normalize();
		return Control(max_accel * distance, time_to);
	}

	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

	Control cruise_control( const b2Vec2& vel, float target_speed, float max_accel )
	{
		float scale = target_speed / vel.Length();
		b2Vec2 target_vel = scale * vel;
		return cruise_control(vel, target_vel, max_accel);
	}

	Control cruise_control( const b2Vec2& vel, const b2Vec2& target_vel, float max_accel )
	{
		b2Vec2 dif = target_vel - vel;
		float L = dif.Length();
		return Control(max_accel/L * dif, L/max_accel);
	}

}
}

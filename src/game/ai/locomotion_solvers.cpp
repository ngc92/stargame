#include "locomotion_solvers.h"
#include "locomotion_control.h"
#include "IPropulsionSystem.h"
#include "game/physics/convert.h"
#include "game/physics/body.h"

#include <boost/range/combine.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <iterator>
#include <iostream>
#include "util/io.h"

namespace game
{
namespace ai
{
	// helper functions in anonymous namespace
	namespace
	{
		struct AppliedControl
		{
			b2Vec2 steer = b2Vec2(0,0);
			float rotate = 0.f;
		};

		/// transforms the controls into the target system and transforms accelerations into forces
		AppliedControl to_target_system(const Control& source, const Body& target)
		{
			AppliedControl control;
			// convert steering variables into a form in which they are useful here
			// transform to local coordinates
			control.steer = local_vector( target, source.steer.value_or(b2Vec2(0,0)) );
			// and make force from acceleration
			control.steer *= target.mass();

			control.rotate = source.rotate.value_or(0.f) * target.inertia();

			return control;
		}

		/// converts the controls to actually possible values, and
		///	returns their total effect.
		AppliedControl make_applied(const propulsion_systems& systems, std::vector<AppliedControl>& controls)
		{
			AppliedControl applied;
			for(const auto& iter : boost::combine( systems, controls ))
			{
				const IPropulsionSystem& system = *iter.get<0>();
				AppliedControl& control = iter.get<1>();
				control.rotate = system.check_rotate( control.rotate );
				applied.rotate += control.rotate;

				control.steer = system.check_thrust( control.steer );
				applied.steer += control.steer;
			}

			return applied;
		}

		float iterate(std::vector<AppliedControl>& controls, AppliedControl desired, AppliedControl real, float threshold)
		{
			b2Vec2 steer_difference = (1.f / controls.size()) * (desired.steer - real.steer);
			float torque_scale = desired.rotate / real.rotate;

			float rot_error = std::abs(desired.rotate - real.rotate) / (std::abs(desired.rotate) + 1e-5);
			float steer_error = steer_difference.Length() / (desired.steer.Length() + 1e-5);
			float error = std::max( rot_error, steer_error );
			if( error < threshold )
				return error;

			for(auto& ctrl : controls)
			{
				ctrl.steer += steer_difference;
				ctrl.rotate *= torque_scale;
			}

			return error;
		}
	}

	std::vector<Control> steer( const propulsion_systems& systems, const Control& control_src, const physics::Body& target )
	{
		const float error_threshold = 0.01;
		auto control = to_target_system(control_src, target);

		// initialise controls by letting all do the same.
		std::vector<AppliedControl> ctrls(systems.size(), control);

		float error;
		// iterative solver
		for(int i = 0; i < 5; ++i)
		{
			AppliedControl real = make_applied(systems, ctrls);
			// now adapt the controls
			error = iterate(ctrls, control, real, error_threshold);
			if(error < error_threshold)
				break;
		}

		// convert back to Control objects
		std::vector<Control> result;
		result.reserve( ctrls.size() );
		boost::transform( ctrls, std::back_inserter(result),
						[&](const AppliedControl& c ){ return Control{c.steer, c.rotate, control_src.time}; } );

		return result;
	}

}
}


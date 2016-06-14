#include "micro_behaviour.h"
#include "game/object_module/IFlightModel.h"
#include "game/object_module/IPropulsionSystem.h"
#include "game/physics/body.h"

#include "locomotion_control.h"
#include "locomotion_solvers.h"
#include <iostream>

namespace game
{
namespace ai
{
	namespace micro_behaviours
	{
        Control get_steering(const MoveTo& behaviour, const IGameObject& target, const ShipInfo& info)
        {
			///! \note this code is not finished!
			Control steer_fly = steer_to_position(target.position(), behaviour.target, target.velocity(),
												info.mMaxThrust / target.body().mass(), info.mMaxVelocity);
			auto steer_vec = steer_fly.steer.get();

			float target_angle = std::atan2( steer_vec.y, steer_vec.x );
			Control target_rotate = rotate_to_angle(target.angle(), target_angle, target.angular_velocity(),
													info.mMaxTorque / target.body().inertia());
			steer_fly.rotate = target_rotate.rotate;
			return steer_fly;
        }

		Control get_steering(const Face& behaviour, const IGameObject& target, const ShipInfo& info)
        {
        	auto steer_vec = behaviour.target - target.position();
        	float target_angle = std::atan2( steer_vec.y, steer_vec.x );
			return rotate_to_angle(target.angle(), target_angle, target.angular_velocity(),
													info.mMaxTorque / target.body().inertia());
        }

        struct visitor : boost::static_visitor<Control>
		{
			visitor(const IGameObject& o, const ShipInfo& i) : object(o), info(i) {}
			const IGameObject& object;
			const ShipInfo& info;

			template<class T>
			Control operator()(const T& t)const
			{
				return get_steering(t, object, info);
			}
		};
	}

	MicroBehaviour::MicroBehaviour( IGameObject& target ) : mInfo(target)
	{

	}

	ShipInfo::ShipInfo(IGameObject& ship)
	{
		IFlightModel& model = *ship.getModuleAsType<IFlightModel>();
		auto& propulsion = model.getPropulsionSystems();
		for(auto& s : propulsion)
		{
			mMaxThrust += s->getMaxThrust();
			mMaxTorque += s->getMaxTorque();
		}

		mMaxVelocity = model.getTerminalVelocity( mMaxThrust );
	}

	void MicroBehaviour::updateShipInfo(IGameObject& ship)
	{
		mInfo = ShipInfo(ship);
	}

	void MicroBehaviour::move_to(b2Vec2 pos)
	{
		mCurrentBehaviour = micro_behaviours::MoveTo{pos};
	}

	void MicroBehaviour::act( IGameObject& object )
	{
		IFlightModel& model = *object.getModuleAsType<IFlightModel>();
		auto& propulsion = model.getPropulsionSystems();

		micro_behaviours::visitor visitor{object, mInfo};
		Control control = mCurrentBehaviour.apply_visitor(visitor);

		auto steering = steer(propulsion, control, object.body());
		for(unsigned i = 0; i < steering.size(); ++i )
		{
			propulsion[i]->thrust( steering[i].steer.get() );
			propulsion[i]->rotate( steering[i].rotate.get() );
		}
	}
}
}

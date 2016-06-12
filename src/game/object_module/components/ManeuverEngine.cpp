#include "ManeuverEngine.h"
#include "game/IGameObject.h"
#include "game/object_module/IFlightModel.h"
#include <iostream>

namespace game
{
namespace components
{
	//! \todo BaseTemperature Parameter
	ManeuverEngine::ManeuverEngine() : CComponent(100, 100, "ManeuverEngine"),
		mThrust( "max_thrust", this, 1000.f ),
		mTorque( "torque", this, 0.1f ),
		mFuelEfficiency( "efficiency", this, 5000 ),
		mLateralControl( "input:lateral_thrust", this, 0.f ),
		mLongitudinalControl( "input:longitudinal_thrust", this, 0.f ),
		mTurnControl( "input:turn", this, 0.f )
	{
	}

	ManeuverEngine::~ManeuverEngine()
	{
	}

	void ManeuverEngine::init(IGameObject& object)
	{
		mTank = getSupplier(object, "fuel");
		mFlightModel = object.getModuleAsType<IFlightModel>();
		assert(mFlightModel);
		mFlightRegistration = IFlightModel::registerPropulsionSystem(mFlightModel, *this);
	}

	void ManeuverEngine::step(IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action)
	{
		auto tank = mTank.lock();
		if(!tank || !mFlightModel ) return;

		b2Vec2 thrust_vec(mLongitudinalControl, mLateralControl);
		if(thrust_vec.LengthSquared() > 1)
			thrust_vec.Normalize();

		float tval = thrust_vec.Length() + 0.001;				// idle consumption 0.1%												// efficiency factor: idle 1, full throttle 0.5

		float fconsum = mThrust / mFuelEfficiency / 50 * tval;	// get the amount of fuel we need for
																// the desired thrust.

		float fuel = tank->getSupply("fuel", fconsum);
		auto thrust = (float)mThrust * fuel / fconsum * tval * thrust_vec;
		mFlightModel->thrust(thrust);
		mFlightModel->rotate((float)mTorque * std::max(-1.f, std::min(1.f, (float)mTurnControl)));
	}

	float ManeuverEngine::getMaxTorque() const
	{
		return mTorque;
	}

	float ManeuverEngine::getMaxThrust() const
	{
		return mThrust;
	}

	void ManeuverEngine::rotate(float rot)
	{
		rot /= mTorque;
		mTurnControl = rot;
	}

	void ManeuverEngine::thrust(const b2Vec2& thr)
	{
		mLateralControl = thr.y / mThrust;
		mLongitudinalControl = thr.x / mThrust;
	}


	// register engine's constructor
	REG_COMP_MACRO(ManeuverEngine);
}
}

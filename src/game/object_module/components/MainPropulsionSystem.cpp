#include "MainPropulsionSystem.h"
#include "game/IGameObject.h"
#include "game/object_module/IFlightModel.h"
#include "game/object_module/IAIModule.h"
#include "consts.h"
#include <iostream>

namespace game
{
namespace components
{
	//! \todo BaseTemperature Parameter
	MainPropulsionSystem::MainPropulsionSystem() : CComponent(100, 100, "MainPropulsionSystem"),
		mThrust( "max_thrust", this, 1000.f ),
		mFuelEfficiency( "efficiency", this, 5000 ),
		mThrustLevel( "input:thrust", this, 0.f ),
		mAfterburner( "input:afterburner", this, 0 )
	{
	}

	MainPropulsionSystem::~MainPropulsionSystem()
	{
	}

	void MainPropulsionSystem::init(IGameObject& object)
	{
		mTank = getSupplier(object, "fuel");
		mFlightModel = object.getModuleAsType<IFlightModel>();
		auto ai = object.getModuleAsType<IAIModule>();
		if(ai)
			mFlightRegistration = ai->registerPropulsionSystem(*this);
		assert(mFlightModel);
	}

	void MainPropulsionSystem::step(IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action)
	{
		auto tank = mTank.lock();
		if(!tank || !mFlightModel ) return;

		float tval = std::min(1.f, std::max(0.f, (float)mThrustLevel)) + 0.001;		// idle consumption 0.1%
		float eta  = (2 - tval) / 2;													// efficiency factor: idle 1, full throttle 0.5

		// afterburner: ridiculous fuel consumption for increased speed
		if( mAfterburner > 0 )
		{
			tval = 1.5;			// 50% extra thrust
			eta = 0.25;			// but 100% extra fuel consumption
		}

		float fconsum = mThrust / mFuelEfficiency * STEP_TIME * tval / eta;	// get the amount of fuel we need for
																			// the desired thrust, i.e. we correct
																			// for eta here.

		float fuel = tank->getSupply("fuel", fconsum);
		float thrust = mThrust * fuel / fconsum * tval;
		mFlightModel->thrust(b2Vec2(thrust, 0));
	}

	float MainPropulsionSystem::getMaxTorque() const
	{
		return 0; // main engine cannot rotate ship.
	}

	float MainPropulsionSystem::getMaxThrust() const
	{
		return mThrust;
	}

	float MainPropulsionSystem::check_rotate( float rot ) const
	{
		return 0;
	}

	b2Vec2 MainPropulsionSystem::check_thrust( const b2Vec2& thrust ) const
	{
		float thrust_fwd = std::max(0.f, thrust.x);
		return b2Vec2(std::min(thrust_fwd, (float)mThrust), 0);

	}
	// action functions
	void MainPropulsionSystem::rotate(float rot)
	{
		// no rotation possible
	}

	void MainPropulsionSystem::thrust(const b2Vec2& thr)
	{
		auto thrust = check_thrust( thr );
		mThrustLevel = thrust.x / mThrust;
	}

	// register engine's constructor
	REG_COMP_MACRO(MainPropulsionSystem);
}
}

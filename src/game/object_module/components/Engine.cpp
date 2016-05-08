#include "Engine.h"
#include "game/IGameObject.h"
#include "game/object_module/IFlightModel.h"
#include <iostream>

namespace game
{
namespace components
{
	//! \todo BaseTemperature Parameter
	Engine::Engine() : CComponent(100, 100, "Engine"),
		mThrust( "max_thrust", this, 1000.f ),
		mFuelEfficiency( "efficiency", this, 5000 ),
		mTorque( "torque", this, 0.1f ),
		mThrustLevel( "input:thrust", this, 0.f ),
		mTurnControl( "input:turn", this, 0.f ),
		mAfterburner( "input:afterburner", this, 0 )
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::init(IGameObject& object)
	{
		mTank = getSupplier(object, "fuel");
		mFlightModel = object.getModuleAsType<IFlightModel>();
		assert(mFlightModel);
	}

	void Engine::step()
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

		float fconsum = mThrust / mFuelEfficiency / 50 * tval / eta;	// get the amount of fuel we need for
																// the desired thrust, i.e. we correct
																// for eta here.

		float fuel = tank->getSupply("fuel", fconsum);
		float thrust = mThrust * fuel / fconsum * tval;
		mFlightModel->thrust(b2Vec2(thrust, 0));
		mFlightModel->rotate((float)mTurnControl * mTorque);
	}

}
}

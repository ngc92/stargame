#include "Engine.h"
#include "Actions.h"
#include "input/IInputCollection.h"
#include <iostream>

namespace game
{
namespace components
{
	//! \todo BaseTemperature Parameter
	Engine::Engine() : CComponent(100, 100, "Engine"),
		mThrust( "thrust", 1.f ), mFuelConsumption( "consumption", 1.f ),
		mThrustLevel( input::createInputElement("thrust", input::InputType::GAUGE, 0.f) )
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::init(IActionListInterface& actions, input::IInputCollection& inputs)
	{
		actions.push(makeResourceRequestAction(*this, "fuel"));
		inputs.addInputElement(mThrustLevel);
	}

	void Engine::step(IActionListInterface& actions)
	{
		if(!mTank) return;

		float tval = std::min(1.f, std::max(0.f, mThrustLevel->value())) + 0.001;		// idle consumption 0.1%
		float eta  = 2 - tval;							// efficiency factor
		float fconsum = mFuelConsumption * tval / eta;	// get the amount of fuel we need for
														// the desired thrust, i.e. we correct
														// for eta here.

		float fuel = mTank->getSupply("fuel", fconsum);
		float thrust = mThrust * fuel / fconsum * tval;
		actions.push(makeThrustAction(*this, b2Vec2(thrust, 0), 0));
	}


	void Engine::registerSupplier(const std::string& resource, IComponent* component)
	{
		if(resource == "fuel")
		{
			mTank = component;
		}
	}
}
}

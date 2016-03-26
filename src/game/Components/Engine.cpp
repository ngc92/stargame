#include "Engine.h"
#include "Actions.h"

namespace game
{
namespace components
{
	//! \todo BaseTemperature Parameter
	Engine::Engine() : CComponent(100, 100, "engine")
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::init(IActionListInterface& actionlist)
	{
		actionlist.push(makeResourceRequestAction(*this, "fuel"));
	}

	void Engine::step(IActionListInterface& actionlist)
	{
		if(!mTank) return;

		float fuel = mTank->getSupply("fuel", 0.001);

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

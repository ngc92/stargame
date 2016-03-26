#include "InputModule.h"
#include "game/GameObject.h"
#include "input/IInputCollection.h"
#include "input/IInputElement.h"
#include "IEngine.h"
#include "IInputManager.h"
#include <iostream>
#include <irrlicht/Keycodes.h>

InputModule::InputModule(IEngine* engine, long myship) :
	mShipID(myship)
{
	/// \todo this is suicide, only for testing!
	engine->getInputManager().addEventListener( std::shared_ptr<InputModule>(this, [](InputModule*){}));
}

void InputModule::onSpawn(const game::GameObject& spawned)
{
	std::cout << "INPUT MODULE ON SPAWN\n";
    if(spawned.getID() != mShipID)
		return;

    // found our ship
	auto& inputs = spawned.getInputs();
    inputs.iterateInputs([this](std::weak_ptr<input::IInputElement>& i){ onInput(i);});
}


void InputModule::onStep(const game::GameWorld& view)
{

}

void InputModule::onInput(std::weak_ptr<input::IInputElement>& input)
{
	auto ip = input.lock();
	if(!ip)
		return;

    std::cout << ip->name() << "\n";
    /// now, we would need an InputMapping definition
    mThrustInput = std::dynamic_pointer_cast<input::IInputGauge>(ip);
}

void InputModule::onKeyEvent(irr::EKEY_CODE key, bool press)
{
	/// \todo here, we would really need timing information
	if(key == irr::KEY_UP && press)
	{
		mThrustInput->setGauge(1);
	} else if(key == irr::KEY_DOWN && press)
	{
		mThrustInput->setGauge(0);
	}
}

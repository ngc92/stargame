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
	for(auto key : mKeysDown)
	{
		auto action = mKeyDownActions.find(key);
		if(action != mKeyDownActions.end())
			action->second();
	}
}

void InputModule::onInput(std::weak_ptr<input::IInputElement>& input)
{
	auto ip = input.lock();
	if(!ip)
		return;

    std::cout << ip->name() << "\n";
    /// now, we would need an InputMapping definition
    mKeyDownActions[irr::KEY_UP] = [ip](){ ip->increase(); };
    mKeyDownActions[irr::KEY_DOWN] = [ip](){ ip->decrease(); };
}

void InputModule::onKeyEvent(irr::EKEY_CODE key, bool press)
{
	/// \todo here, we would really need timing information
	if(press)
	{
		mKeysDown.insert(key);
		auto action = mKeyPressActions.find(key);
		if(action != mKeyPressActions.end())	action->second();
	} else {
		mKeysDown.erase(key);
		auto action = mKeyReleaseActions.find(key);
		if(action != mKeyReleaseActions.end())	action->second();
	}
}

#include "InputModule.h"
#include "game/IGameObject.h"
#include "input/IInputElement.h"
#include "input/CInputConfig.h"
#include "game/IGameWorldView.h"
#include "game/view_thread/IViewThreadGO.h"
#include "IEngine.h"
#include "IInputManager.h"
#include <iostream>
#include <irrlicht/Keycodes.h>
#include <boost/algorithm/string/predicate.hpp>

using namespace std::placeholders;

InputModule::InputModule(IEngine* engine, long myship) :
	mShipID(myship), mInputConfig( make_unique<input::CInputConfig>() )
{
	/// \todo this is suicide, only for testing!
	engine->getInputManager().addEventListener( std::shared_ptr<InputModule>(this, [](InputModule*){}));
	mInputConfig->load();
}

InputModule::~InputModule()
{
}

void InputModule::init()
{
	mSpawnLst = world().addSpawnListener(std::bind(&InputModule::onSpawn, this, _1));
}

void InputModule::onSpawn(const game::IGameObjectView& spawned)
{
	std::cout << "INPUT MODULE ON SPAWN\n";
	if(spawned.id() != mShipID)
		return;

	// found our ship
	spawned.forallProperties(std::bind(&InputModule::propertyCallback, this, _1));

	// no longer need the spawn listener.
	mSpawnLst = ListenerRef();
}


void InputModule::onStep()
{
	for(auto& elem : mInputElements)
		elem->onStep();
}

void InputModule::propertyCallback(property::IPropertyView& property)
{
	auto name = property.name();
	if(!boost::algorithm::starts_with(name, "input:"))
		return;

	std::cout << "INPUT: " << property.path() << "\n";
	auto input = mInputConfig->getInputElemt(property);
	if(input)
	{
		mInputElements.push_back( std::move(input) );
	}
}

void InputModule::onKeyEvent(irr::EKEY_CODE key, bool press)
{
	for(auto& elem : mInputElements)
	{
		elem->onKeyEvent(key, press ? input::KeyState::PRESSED : input::KeyState::RELEASED );
	}
}

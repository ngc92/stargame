#include "InputModule.h"
#include "game/IGameObject.h"
#include "input/IInputElement.h"
#include "input/CInputConfig.h"
#include "game/IGameWorldView.h"
#include "IEngine.h"
#include "IInputManager.h"
#include <iostream>
#include <irrlicht/Keycodes.h>
#include <boost/algorithm/string/predicate.hpp>

using namespace std::placeholders;

InputModule::InputModule(IEngine* engine, uint64_t myship) :
	mShipID(myship), mInputConfig( std::make_unique<input::CInputConfig>() )
{
	/// \todo this is suicide, only for testing!
	engine->getInputManager().addEventListener( std::shared_ptr<InputModule>(this, [](InputModule*){}));
	mInputConfig->load();
}

InputModule::~InputModule()
{
}

void InputModule::init(game::IGameWorldView& world_view)
{
	mSpawnLst = world_view.addSpawnListener(std::bind(&InputModule::onSpawn, this, _1));
}

void InputModule::onSpawn(game::IGameObjectView& spawned)
{
	std::cout << "INPUT MODULE ON SPAWN\n";
	if(spawned.id() != mShipID)
		return;

	// save the object into a shared_ptr to ensure that
	// it does not get destroyed prematurely.
	mControlledObject = spawned.shared_from_this();
	mRemLst = spawned.addRemoveListener( std::bind(&InputModule::reset, this ) );

	// found our ship
	spawned.forallProperties(std::bind(&InputModule::propertyCallback, this, _1));

	// no longer need the spawn listener.
	mSpawnLst = ListenerRef();
}


void InputModule::step( game::IGameWorldView& world_view )
{
	mActions.clear();
	for(auto& elem : mInputElements)
	{
		auto result = elem->onStep();
		if(result)
		{
			game::view_thread::Action action;
			action.target_id = mShipID;
			action.action = std::move(result);
			mActions.push_back( std::move(action) );
		}
	}
}

void InputModule::reset()
{
	mInputElements.clear();
	mControlledObject.reset();
	mRemLst = ListenerRef();
}

void InputModule::propertyCallback(property::IPropertyView& property)
{
	auto name = property.name();
	if(!boost::algorithm::starts_with(name, "input:"))
		return;

	std::cout << "INPUT: " << property.path() << " ";
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

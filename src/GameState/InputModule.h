#ifndef INPUTMODULE_H_INCLUDED
#define INPUTMODULE_H_INCLUDED

#include "IGameModule.h"
#include "IEventListener.h"
#include <memory>

class IEngine;
namespace input
{
	class IInputElement;
	class IInputGauge;
}

class InputModule : public IGameModule, public IEventListener
{
public:
	InputModule(IEngine*, long myship);

	void onSpawn(const game::GameObject& spawned) override;
	void onStep(const game::GameWorld& view) override;

	void registerListener( const IInputManager* mgr) override {}
	void onKeyEvent(irr::EKEY_CODE key, bool press) override;
	void onMouseClickEvent(irr::E_MOUSE_BUTTON_STATE_MASK button, bool click, int x, int y) override {};
private:
	void onInput(std::weak_ptr<input::IInputElement>& input);

	long mShipID;
	std::shared_ptr<input::IInputGauge> mThrustInput;
};

#endif // INPUTMODULE_H_INCLUDED

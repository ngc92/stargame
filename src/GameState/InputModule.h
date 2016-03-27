#ifndef INPUTMODULE_H_INCLUDED
#define INPUTMODULE_H_INCLUDED

#include "IGameModule.h"
#include "IEventListener.h"
#include <memory>
#include <map>
#include <set>

class IEngine;
namespace input
{
	class IInputElement;
	class IInputConfig;
	enum class KeyAction : int;
}

class InputModule : public IGameModule, public IEventListener
{
public:
	InputModule(IEngine*, long myship);
	~InputModule();

	void onSpawn(const game::GameObject& spawned) override;
	void onStep(const game::GameWorld& view) override;

	void registerListener( const IInputManager* mgr) override {}
	void onKeyEvent(irr::EKEY_CODE key, bool press) override;
	void onMouseClickEvent(irr::E_MOUSE_BUTTON_STATE_MASK button, bool click, int x, int y) override {};
private:
	void onInput(std::weak_ptr<input::IInputElement>& input);
	long mShipID;
	std::unique_ptr<input::IInputConfig> mInputConfig;

	using key_mapping_t = std::map<irr::EKEY_CODE, std::function<void()>>;
	key_mapping_t mKeyPressActions;
	key_mapping_t mKeyReleaseActions;
	key_mapping_t mKeyDownActions;

	key_mapping_t& getKeyMap(input::KeyAction action);


	std::set<irr::EKEY_CODE> mKeysDown;

};

#endif // INPUTMODULE_H_INCLUDED

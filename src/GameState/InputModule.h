#ifndef INPUTMODULE_H_INCLUDED
#define INPUTMODULE_H_INCLUDED

#include "game/IGameViewModule.h"
#include "IEventListener.h"
#include "listener/listener.h"
#include <memory>
#include <map>
#include <set>

namespace property
{
	class IPropertyView;
}

class IEngine;

namespace game
{
	class IGameObjectView;
}

namespace input
{
	class IInputElement;
	class IInputConfig;
}

class InputModule : public game::IGameViewModule, public IEventListener
{
public:
	InputModule(IEngine*, uint64_t myship);
	~InputModule();

	void step( game::IGameWorldView& world_view ) override;
	void init( game::IGameWorldView& world_view ) override;

	void registerListener( const IInputManager* mgr) override {}
	void onKeyEvent(irr::EKEY_CODE key, bool press) override;
	void onMouseClickEvent(irr::E_MOUSE_BUTTON_STATE_MASK button, bool click, int x, int y) override {};
private:
	void onSpawn( game::IGameObjectView& spawned );
	void propertyCallback( property::IPropertyView& pview);
	void reset();
	uint64_t mShipID;
	std::unique_ptr<input::IInputConfig> mInputConfig;
	std::vector<std::shared_ptr<input::IInputElement>> mInputElements;
	ListenerRef mSpawnLst;
	ListenerRef mRemLst;

	std::shared_ptr<game::IGameObjectView> mControlledObject;
};

#endif // INPUTMODULE_H_INCLUDED

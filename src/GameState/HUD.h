#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include "game/IGameViewModule.h"
#include "util.h"
#include "listener/listenerlist.h"

namespace game
{
	class IGameObjectView;
}

namespace property
{
	class IPropertyObjectView;
}

namespace irr
{
	namespace gui
	{
		class IGUIEnvironment;
	}
}

namespace graphic
{
	class SubsystemDamageView;
	class IShipStatusView;
	class ITacticalMapView;
	class ShipStatusControl;
	class TacticalMapCtrl;
}

class HUD : public game::IGameViewModule
{
public:
	HUD(irr::gui::IGUIEnvironment* env, long ship);
	~HUD();

	void init( game::IGameWorldView& world_view  ) override;
	void step( game::IGameWorldView& world_view ) override {};
private:
	void onSpawn(const game::IGameObjectView& spawned);

	// processing
	void processChild(const property::IPropertyObjectView& child);

	long mShipID;
	irr::gui::IGUIEnvironment* mGUIEnv;
	graphic::SubsystemDamageView* mDmgView;
	graphic::IShipStatusView* mStaView;
	graphic::ITacticalMapView* mTacMap;
	std::unique_ptr<graphic::ShipStatusControl> mStatCtrl;
	std::unique_ptr<graphic::TacticalMapCtrl> mTacCtrl;
	std::vector<ListenerRef> mListeners;
};

#endif // HUD_H_INCLUDED

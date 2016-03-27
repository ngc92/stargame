#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include "IGameModule.h"
#include "util.h"
#include "util/ListenerList.h"

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
}

class HUD : public IGameModule
{
public:
	HUD(irr::gui::IGUIEnvironment* env, long ship);

	void onSpawn(const game::GameObject& spawned) override;
	void onStep(const game::GameWorld& view) override {};
private:
	long mShipID;
	irr::gui::IGUIEnvironment* mGUIEnv;
	graphic::SubsystemDamageView* mDmgView;
	std::vector<ListenerRef> mListeners;
};

#endif // HUD_H_INCLUDED

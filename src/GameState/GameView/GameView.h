#ifndef GAMEVIEW_H_INCLUDED
#define GAMEVIEW_H_INCLUDED

#include "game/CGameViewModule.h"
#include "util.h"
#include "property/property.h"

namespace gfx
{
	class GameViewGFX;
}

class GameView : public game::CGameViewModule
{
public:
	GameView( irr::IrrlichtDevice* device );
	~GameView();

	void init() override;
	void onStep() override {};
private:
	void onSpawn(game::IGameObjectView& spawned);

	std::vector<ListenerRef> mListeners;
	std::vector<ListenerRef> mRemoveListenerDump;

	std::unique_ptr<gfx::GameViewGFX> mGFX;
};

#endif // GAMEVIEW_H_INCLUDED

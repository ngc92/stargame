#ifndef GAMEVIEW_H_INCLUDED
#define GAMEVIEW_H_INCLUDED

#include "game/IGameViewModule.h"
#include "util.h"
#include "property/property.h"

namespace gfx
{
	class GameViewGFX;
}

class GameView : public game::IGameViewModule
{
public:
	GameView( irr::IrrlichtDevice* device );
	~GameView();

	void init( game::IGameWorldView& world_view  ) override;
	void step( game::IGameWorldView& world_view ) override {};
private:
	void onSpawn(game::IGameObjectView& spawned);

	std::vector<ListenerRef> mListeners;
	std::vector<ListenerRef> mRemoveListenerDump;

	std::unique_ptr<gfx::GameViewGFX> mGFX;
};

#endif // GAMEVIEW_H_INCLUDED

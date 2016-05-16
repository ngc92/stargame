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
	void onSpawn(const game::IGameObjectView& spawned);

	// processing
	void processChild(const property::IPropertyObjectView& child);
	std::vector<ListenerRef> mListeners;
	
	std::unique_ptr<gfx::GameViewGFX> mGFX;
};

#endif // GAMEVIEW_H_INCLUDED

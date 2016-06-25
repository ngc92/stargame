#include "GameView.h"
#include "util.h"
#include "game/IGameWorldView.h"
#include "game/IGameObjectView.h"
#include "GameViewGFX.h"
#include <iostream>

GameView::GameView(irr::IrrlichtDevice* device) : mGFX( std::make_unique<gfx::GameViewGFX>( device ) )
{

}

GameView::~GameView()
{

}

void GameView::init( game::IGameWorldView& world_view  )
{
	using std::placeholders::_1;
	mListeners.push_back(world_view.addSpawnListener(std::bind(&GameView::onSpawn, this, _1)));

	mGFX->init();
}


void GameView::onSpawn(game::IGameObjectView& spawned)
{
	/// \todo load the model based on embedded data
	auto type = spawned.category();
	/// \todo find a better way to keep track of those listeners! Remove when they are done!
	mRemoveListenerDump.push_back(mGFX->addShip(spawned, (int)type));
}

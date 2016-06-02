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

void GameView::init()
{
	using std::placeholders::_1;
	mListeners.push_back(world().addSpawnListener(std::bind(GameView::onSpawn, this, _1)));

	mGFX->init();
}


void GameView::onSpawn(game::IGameObjectView& spawned)
{
	/// \todo load the model based on embedded data
	auto type = boost::get<std::string>(spawned.getProperty("_type_").value());
	std::cout << type << "\n";
	/// \todo find a better way to keep track of those listeners! Remove when they are done!
	mRemoveListenerDump.push_back(mGFX->addShip(spawned, type));
}

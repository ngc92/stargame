#include "GameState.h"
#include "game/Game.h"
#include "IEngine.h"
#include "util.h"
#include "TextInterface/TextInterface.h"
#include "InputModule.h"
#include "HUD.h"
#include "debug/CDebugDraw.h"
#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/IrrlichtDevice.h>
#include <iostream>


GameState::GameState(IEngine* engine) :
	mGUIEnv(engine->getGUIEnvironment()),
	mGame( make_unique<game::Game>() ),
	mDebugDraw( std::make_shared<CDebugDraw>( engine->getIrrlichDevice().getVideoDriver() ) )
{
	//addGameModule(std::make_shared<TextInterface>());
	addGameModule(std::make_shared<InputModule>(engine, 0));
	addGameModule(std::make_shared<HUD>(mGUIEnv, 0));
	addGameModule(mDebugDraw);
}

GameState::~GameState()
{
};

void GameState::update()
{
	mGame->step();
	for(auto& module : mModules)
		module->step();
}

void GameState::onDraw()
{
	mGUIEnv->drawAll();
	mDebugDraw->doDraw();
}

void GameState::onActivate()
{
	// register all listeners
	mGame->run();
}

void GameState::onDeactivate() noexcept
{

}

const char* GameState::getName() const noexcept
{
	return "Game";
}

IGUIEnvironment* GameState::getGUIEnvironment() noexcept
{
	return mGUIEnv;
}

bool GameState::onEvent(const irr::SEvent::SGUIEvent& event)
{
	return false;
}

void GameState::addGameModule(std::shared_ptr<game::IGameViewModule> module)
{
	mGame->addModule( module );
	mModules.push_back( std::move(module) );
}

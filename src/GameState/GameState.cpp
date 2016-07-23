#include "GameState.h"
#include "game/Game.h"
#include "game/IGameWorld.h"
#include "IEngine.h"
#include "util.h"
#include "TextInterface/TextInterface.h"
#include "GameView/GameView.h"
#include "InputModule.h"
#include "HUD.h"
#include "debug/CDebugDraw.h"
#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/ISceneManager.h>
#include <irrlicht/IrrlichtDevice.h>
#include <iostream>


GameState::GameState(IEngine* engine) :
	mGUIEnv(engine->getGUIEnvironment()),
	mSceneMgr( engine->getIrrlichDevice().getSceneManager() ),
	mGame( std::make_unique<game::Game>() ),
	mDebugDraw( std::make_shared<CDebugDraw>( engine->getIrrlichDevice().getVideoDriver() ) ),
	mInputModule(std::make_shared<InputModule>(engine, 0))
{
	addGameModule(std::make_shared<GameView>( &engine->getIrrlichDevice() ));
	addGameModule(mInputModule);
	addGameModule(std::make_shared<HUD>(mGUIEnv, 0));
	
	mGame->getSimulationWorld().addModule( mDebugDraw );
}

GameState::~GameState()
{
};

void GameState::update()
{
	for(auto& a : mInputModule->getActions())
	{
		mGame->getActionStream().push(a);
	}
	mGame->getActionStream().publish();
	mGame->step();
}

void GameState::onDraw()
{
	mSceneMgr->drawAll();
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
	mGame->getSimulationWorld().addModule( module );
	mModules.push_back( std::move(module) );
}

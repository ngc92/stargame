#include "GameState.h"
#include "game/Game.h"
#include "IEngine.h"
#include "util.h"
#include "TextInterface/TextInterface.h"
#include "InputModule.h"
#include <irrlicht/IGUIEnvironment.h>
#include <iostream>

GameState::GameState(IEngine* engine) :
	mGUIEnv(engine->getGUIEnvironment()),
	mGame( make_unique<game::Game>() ),
	mSpawnListener( mGame->addSpawnListener( [this](const game::GameObject& s) { onSpawn( s ); } ) )
{
	addGameModule(make_unique<TextInterface>());
	addGameModule(make_unique<InputModule>(engine, 0));
}

GameState::~GameState()
{
};

void GameState::update()
{
	mGame->executeThreadSaveReader( [this](const game::GameWorld& world){ onGameStep(world); } );
}

void GameState::onGameStep(const game::GameWorld& world)
{
	for(auto& module : mModules)
		module->onStep(world);
}

void GameState::onSpawn( const game::GameObject& object)
{
	for(auto& module : mModules)
		module->onSpawn(object);
}

void GameState::onDraw()
{
	mGUIEnv->drawAll();
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

void GameState::addGameModule(std::unique_ptr<IGameModule> module)
{
	mModules.push_back( std::move(module) );
}

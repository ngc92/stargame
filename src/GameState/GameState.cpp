#include "GameState.h"
#include "game/Game.h"
#include "IEngine.h"
#include "util.h"
#include "TextInterface/TextInterface.h"
#include <irrlicht/IGUIEnvironment.h>
#include <iostream>

GameState::GameState(IEngine* engine) :
	mGUIEnv(engine->getGUIEnvironment()),
	mGame( make_unique<game::Game>() ),
	mInterface( make_unique<TextInterface>() ),
	mSpawnListener( mGame->addSpawnListener( [this](const game::GameObject& s) { mInterface->onSpawn( s ); } ) )
{
}

GameState::~GameState(){};

void GameState::update()
{
	mGame->executeThreadSaveReader( [this](const game::GameWorld& world){ mInterface->update( world ); } );
}

void GameState::onDraw()
{
	mGUIEnv->drawAll();
}

void GameState::onActivate()
{
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

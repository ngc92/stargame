#include "Game.h"
#include "IGameWorld.h"
#include "view_thread/CSimulationThreadWriter.h"
#include "view_thread/CViewThreadReader.h"
#include "view_thread/EventStream.h"
#include "view_thread/ActionStream.h"
#include "physics/body.h"
#include "IGameObject.h"
#include "IGameViewModule.h"
#include "util.h"
#include "CTimeManager.h"
#include "spawn/CSpawnManager.h"
#include "spawn/SpawnData.h"
#include <iostream>

namespace game
{
	Game::Game() :
		mRunGame(false),
		mQuitGame(false),
		mGameThread( [this](){ gameloop(); } ),
		mGameWorld( createSimulationWorld() ),
		mTimeManager( std::make_unique<CTimeManager>() ),
		mSpawnManager( std::make_unique<spawn::CSpawnManager>( ) ),
		mWorldView( createObservationWorld() ),
		mEventStream( std::make_unique<view_thread::EventStream>()),
		mActionStream( std::make_unique<view_thread::ActionStream>()),
		mExportModule( std::make_shared<view_thread::CSimulationThreadWriter>( *mEventStream ) ),
		mImportModule( std::make_shared<view_thread::CViewThreadReader>( *mEventStream ) )
	{
		mTimeManager->setDesiredFPS(50);
		mGameWorld->addModule( mExportModule );
		mWorldView->addModule( mImportModule );
	};
	Game::~Game()
	{
		mQuitGame = true;
		mGameThread.join();
	};

	void Game::run()
	{
		auto world = mGameWorld.get();
		mSpawnManager->spawn(*world, spawn::SpawnData(ObjectCategory::SPACESHIP, "Destroyer", b2Vec2(0,0)).set_id(0));
		mSpawnManager->spawn(*world, spawn::SpawnData(ObjectCategory::SPACESHIP, "Destroyer", b2Vec2(50,50)).set_id(1));
		mRunGame = true;
	}

	void Game::pause()
	{
		mRunGame = false;
	}

	void Game::step()
	{
		mWorldView->step( *mSpawnManager );
	}

	void Game::gameloop()
	{
		while(!mQuitGame)
		{
			if(mRunGame)
			{
				mTimeManager->waitTillNextFrame();
				// perform all queued actions
				mActionStream->update();
				for(auto& action : mActionStream->read())
				{
					auto& target = mGameWorld->getObjectByID(action.target_id);
					action.action(target);
				}
				
				// update the world
				mGameWorld->step( *mSpawnManager );
			}
		}
	}

	void Game::addModule(std::weak_ptr<IGameViewModule> module)
	{
		mWorldView->addModule( std::move(module) );
	}

}

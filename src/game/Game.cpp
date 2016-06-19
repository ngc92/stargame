#include "Game.h"
#include "CGameWorld.h"
#include "view_thread/CViewThreadGW.h"
#include "view_thread/CSimulationThreadWriter.h"
#include "view_thread/CViewThreadReader.h"
#include "view_thread/EventStream.h"
#include "IGameObject.h"
#include "IGameViewModule.h"
#include "util.h"
#include "CTimeManager.h"
#include "spawn/CSpawnManager.h"
#include "spawn/SpawnData.h"

namespace game
{
	Game::Game() :
		mRunGame(false),
		mQuitGame(false),
		mGameThread( [this](){ gameloop(); } ),
		mGameWorld( std::make_unique<CGameWorld>() ),
		mTimeManager( std::make_unique<CTimeManager>() ),
		mSpawnManager( std::make_unique<spawn::CSpawnManager>( ) ),
		mWorldView( std::make_unique<CGameWorld>( ) ),
		mEventStream( std::make_unique<view_thread::EventStream>()),
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
		mSpawnManager->spawn(*world, spawn::SpawnData(spawn::SpawnType::SPACESHIP, "Destroyer", b2Vec2(0,0)).set_id(0));
		mSpawnManager->spawn(*world, spawn::SpawnData(spawn::SpawnType::SPACESHIP, "Destroyer", b2Vec2(50,50)).set_id(1));
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
				// update the world
				mGameWorld->step( *mSpawnManager );
			}
		}
	}

	void Game::addModule(std::weak_ptr<IGameViewModule> module)
	{
		auto locked = module.lock();
		if(locked)
		{
			locked->init( *mWorldView );
			mWorldView->addModule( std::move(module) );
		}
	}

}

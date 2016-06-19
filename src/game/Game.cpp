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
		mWorldView( std::make_unique<view_thread::CViewThreadGameWorld>( *mGameWorld ) ),
		mEventStream( std::make_unique<view_thread::EventStream>()),
		mExportModule( std::make_shared<view_thread::CSimulationThreadWriter>( *mEventStream ) ),
		mImportModule( std::make_shared<view_thread::CViewThreadReader>( *mEventStream ) )
	{
		mTimeManager->setDesiredFPS(50);
		mExportModule->init(*mGameWorld);
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
		mWorldView->step();
		for(auto& mod : mModules)
		{
			auto locked = mod.lock();
			if(locked)
			{
				std::lock_guard<std::mutex> lock( mWorldView->getUpdateMutex() );
				locked->step( *mWorldView );
			}
		}

		mImportModule->step(*mWorldView);
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

				// update the world references
				mWorldView->update();

				mExportModule->step(*mGameWorld);

				// update modules
				std::lock_guard<std::mutex> lock(mModuleMutex);
				// remove old modules
				/// \todo
			}
		}
	}

	WorldView& Game::getWorldView()
	{
		return *mWorldView;
	}

	void Game::addModule(std::weak_ptr<IGameViewModule> module)
	{
		std::lock_guard<std::mutex> lock(mModuleMutex);
		auto locked = module.lock();
		if(locked)
		{
			locked->init( *mWorldView );
			mModules.push_back( std::move(module) );
		}
	}

}

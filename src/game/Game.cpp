#include "Game.h"
#include "CGameWorld.h"
#include "view_thread/CViewThreadGW.h"
#include "IGameObject.h"
#include "IGameViewModule.h"
#include "util.h"
#include "CTimeManager.h"
#include "spawn/CSpawnManager.h"
#include "spawn/SpawnData.h"
#include <Box2D/Box2D.h>

namespace game
{
	Game::Game() :
		mRunGame(false),
		mQuitGame(false),
		mGameThread( [this](){ gameloop(); } ),
		mGameWorld( make_unique<CGameWorld>() ),
		mTimeManager( make_unique<CTimeManager>() ),
		mSpawnManager( make_unique<spawn::CSpawnManager>( ) ),
		mWorldView( make_unique<view_thread::CViewThreadGameWorld>( *mGameWorld ) )
	{
		mTimeManager->setDesiredFPS(50);
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
		/// \todo should we step modules here?
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

				// update modules
				for(auto& mod : mModules)
				{
					auto locked = mod.lock();
					if(locked)
						locked->onGameStep(*mGameWorld);
				}

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
			locked->setStepMutex( &mWorldView->getUpdateMutex() );
			locked->setWorldView( mWorldView.get() );
			locked->init();
			mModules.push_back( std::move(module) );
		}
	}

}

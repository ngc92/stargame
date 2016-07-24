#include "Game.h"
#include "IGameWorld.h"
#include "threading/CSimulationThreadWriter.h"
#include "threading/CViewThreadReader.h"
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
		mEventStream( std::make_unique<threading::EventStream>()),
		mActionStream( std::make_unique<threading::ActionStream>()),
		mExportModule( std::make_shared<threading::CSimulationThreadWriter>( *mEventStream ) ),
		mImportModule( std::make_shared<threading::CViewThreadReader>( *mEventStream ) )
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
					// the object might be dead by now, then just ignore the action
					auto target = mGameWorld->getObjectPtrByID(action.target_id);
					if(target)
						action.action(*target);
				}
				
				// update the world
				mGameWorld->step( *mSpawnManager );
			}
		}
	}

	IGameWorld& Game::getSimulationWorld() const
	{
		return *mWorldView;
	}

}

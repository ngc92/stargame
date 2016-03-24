#include "Game.h"
#include "GameWorld.h"
#include "util.h"

namespace game
{
	Game::Game() :
		mRunGame(false),
		mQuitGame(false),
		mGameThread( [this](){ gameloop(); } ),
        mGameWorld( make_unique<GameWorld>() )
	{

	};
	Game::~Game()
	{
		mQuitGame = true;
		mGameThread.join();
	};

	void Game::run()
	{
		mRunGame = true;
	}

	void Game::pause()
	{
		mRunGame = false;
	}

	void Game::gameloop()
	{
		while(!mQuitGame)
		{
			if(mRunGame)
			{
				// update the world
				mGameWorld->step(1.0/60);
				// now start communicating to the outside.
				outgoing_com();

			}
		}
	}

	void Game::outgoing_com()
	{
		// listeners, that are called every step
		mStepListeners.notify();
	}
}

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
				auto lock = mLock.lock_write();
				// update the world
				mGameWorld->step(1.0/60);
			}
		}
	}

	void Game::executeThreadSaveReader(std::function<void(const GameWorld&)> reader) const
	{
		auto lock = mLock.lock_read();
		reader(*mGameWorld);
	}

}

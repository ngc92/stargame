#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <thread>
#include <memory>
#include <atomic>
#include <functional>
#include "util/WriteLock.h"

namespace game
{
	class GameWorld;

	/*! \class Game
		\brief Class responsible for a game.
		\details This class manages a game and provides
				the glue between the game thread and
				any external observers.
	*/
	class Game
	{
	public:
		Game();
		~Game();

		void run();
		void pause();

		/*! \brief executes code from another thread
			\details This function allows another thread to register
					actions for execution, which will be guaranteed
					to be executed non-interleaved with the game
					simulation, and thus be able to read game data.
		*/
		void executeThreadSaveReader(std::function<void(const GameWorld&)> reader) const;

	private:
		void gameloop();

		std::atomic<bool> mRunGame;
		std::atomic<bool> mQuitGame;
		std::thread mGameThread;
		std::unique_ptr<GameWorld> mGameWorld;

		WriteLock mLock;
	};
}

#endif // GAME_H_INCLUDED

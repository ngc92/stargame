#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <thread>
#include <memory>
#include <atomic>
#include "util/ListenerList.h"

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

		// register listeners

	private:
		void gameloop();

		void outgoing_com();

		std::atomic<bool> mRunGame;
		std::atomic<bool> mQuitGame;
		std::thread mGameThread;
		std::unique_ptr<GameWorld> mGameWorld;

		ListenerList<void> mStepListeners;
	};
}

#endif // GAME_H_INCLUDED

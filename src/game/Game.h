#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <thread>
#include <memory>
#include <atomic>
#include <unordered_map>
#include <functional>
#include "util/WriteLock.h"
#include "util/ListenerList.h"

namespace game
{
	class GameWorld;
	class GameObject;

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

		/*! \brief registeres a spawn listener to the world
			\details This spawn listener is only executed once the
					game world is in locked state.
		*/
		template<class T>
		ListenerRef addSpawnListener(T&& f) { return _addSpawnListener( f ); };

	private:

		ListenerRef _addSpawnListener(std::function<void(const GameObject&)> lst);

		void gameloop();

		std::atomic<bool> mRunGame;
		std::atomic<bool> mQuitGame;
		std::thread mGameThread;
		std::unique_ptr<GameWorld> mGameWorld;

		struct ListenerQueue;
		std::unordered_map<std::thread::id, std::unique_ptr<ListenerQueue>> mListenerQueues;

		WriteLock mLock;
	};
}

#endif // GAME_H_INCLUDED

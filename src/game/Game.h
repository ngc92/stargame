#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <thread>
#include <memory>
#include <atomic>
#include <functional>
#include "listener/listenerlist.h"

class ITimeManager;

namespace game
{
	class IGameWorld;
	class IGameObject;
	class IGameViewModule;
	class IGameModule;
	namespace spawn
	{
		class ISpawnManager;
	}

	namespace view_thread
	{
		class EventStream;
		class ActionStream;
	}


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

		/// call from view threads
		void step();

		/// adds a module to the module list in a thread-save manner.
		void addModule(std::weak_ptr<IGameViewModule> module);
		
		view_thread::ActionStream& getActionStream() { return *mActionStream; }

	private:
		void gameloop();

		std::atomic<bool> mRunGame;
		std::atomic<bool> mQuitGame;
		std::thread mGameThread;
		std::unique_ptr<IGameWorld> mGameWorld;
		std::unique_ptr<ITimeManager> mTimeManager;
		std::unique_ptr<spawn::ISpawnManager> mSpawnManager;

		std::unique_ptr<IGameWorld> mWorldView;
		std::unique_ptr<view_thread::EventStream> mEventStream;
		std::unique_ptr<view_thread::ActionStream> mActionStream;
		std::shared_ptr<IGameViewModule> mExportModule;
		std::shared_ptr<IGameModule> mImportModule;
	};
}

#endif // GAME_H_INCLUDED

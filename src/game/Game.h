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
	class SpawnManager;
	namespace view_thread
	{
		class IViewThreadGameWorld;
	}
	
	using WorldView = view_thread::IViewThreadGameWorld;

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
		
		WorldView& getWorldView();
		
		/// adds a module to the module list in a thread-save manner.
		void addModule(std::weak_ptr<IGameViewModule> module);

	private:
		void gameloop();

		std::atomic<bool> mRunGame;
		std::atomic<bool> mQuitGame;
		std::thread mGameThread;
		std::unique_ptr<IGameWorld> mGameWorld;
		std::unique_ptr<ITimeManager> mTimeManager;
		std::unique_ptr<SpawnManager> mSpawnManager;
		
		std::unique_ptr<view_thread::IViewThreadGameWorld> mWorldView;
		
		std::mutex mModuleMutex;
		std::vector<std::weak_ptr<IGameViewModule>> mModules;
	};
}

#endif // GAME_H_INCLUDED

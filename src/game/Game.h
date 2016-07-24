#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <thread>
#include <memory>
#include <atomic>
#include <functional>
#include "listener/listenerlist.h"
#include "threading/ThreadStreams.h"

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

		/// gets the simulation world.
		IGameWorld& getSimulationWorld() const;
		
		threading::ActionStream& getActionStream() { return *mActionStream; }

	private:
		void gameloop();

		std::atomic<bool> mRunGame;
		std::atomic<bool> mQuitGame;
		std::thread mGameThread;
		std::unique_ptr<IGameWorld> mGameWorld;
		std::unique_ptr<ITimeManager> mTimeManager;
		std::unique_ptr<spawn::ISpawnManager> mSpawnManager;

		std::unique_ptr<IGameWorld> mWorldView;
		//! stream that goes from the simulation world to the view world
		std::unique_ptr<threading::EventStream> mEventStream;
		//! stream that goes from view to simulation
		std::unique_ptr<threading::ActionStream> mActionStream;
		std::shared_ptr<IGameViewModule> mExportModule;
		std::shared_ptr<IGameModule> mImportModule;
	};
}

#endif // GAME_H_INCLUDED

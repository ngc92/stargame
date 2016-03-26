#include "Game.h"
#include "GameWorld.h"
#include "GameObject.h"
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

	struct Game::ListenerQueue : noncopyable
	{
		std::mutex mProtection;
		std::vector<std::function<void()>> mTriggered;

		void push(std::function<void()> f)
		{
			std::lock_guard<std::mutex> lck(mProtection);
            mTriggered.push_back( std::move(f) );
		}

		void process()
		{
			std::vector<std::function<void()>> copy;
			{
				std::lock_guard<std::mutex> lck(mProtection);
				std::swap(copy, mTriggered);
			}
			for(auto& f : copy)
				f();
		}
	};

	void Game::executeThreadSaveReader(std::function<void(const GameWorld&)> reader) const
	{
		auto lock = mLock.lock_read();
		// first, process all queued events
		if(mListenerQueues.count(std::this_thread::get_id()) != 0)
		{
			mListenerQueues.at(std::this_thread::get_id())->process();
		}

		reader(*mGameWorld);
	}

	ListenerRef Game::_addSpawnListener(std::function<void(const GameObject&)> listener)
	{
		std::thread::id id = std::this_thread::get_id();

		if(mListenerQueues.count(id) == 0)
		{
			mListenerQueues[id] = make_unique<ListenerQueue>();
		}

		ListenerQueue& queue = *mListenerQueues.at(id);

		/// \todo c++14: use move capture here
		auto wrapped = [&queue, listener](GameObject& o)
		{
			// get a reference to the game object that we can keep until it is time
			// to process the listener.
			std::weak_ptr<const GameObject> cache( o.shared_from_this() );
			queue.push( [cache, listener](){
						auto ptr = cache.lock();
						if(ptr)
							listener(*ptr);
						}
					);
		};

		/// \todo this is currently not a thread save operation
		return mGameWorld->addSpawnListener( wrapped );
	}

}

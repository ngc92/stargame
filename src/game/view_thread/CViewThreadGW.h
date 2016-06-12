#ifndef CVIEWTHREADGW_H_INCLUDED
#define CVIEWTHREADGW_H_INCLUDED

#include "IViewThreadGW.h"
#include <unordered_map>
#include "listener/listenerlist.h"

namespace game
{
	namespace view_thread
	{
		class IViewThreadGameObject;

		class CViewThreadGameWorld : public IViewThreadGameWorld
		{
		public:
			CViewThreadGameWorld(IGameWorldView& world);

			/// gets the number of objects that are currently registered in the world.
			std::size_t object_count() const final;

			/// adds a listener that is called whenever a new game objects is spawned in the world.
			/// \note This is thread-safe.
			ListenerRef addSpawnListener(std::function<void(IGameObjectView&)> f) final;

			/// iterates over all game objects \p o inside this world and calls \p f(o).
			void iterateAllObjects(const std::function<void(IGameObjectView&)>& f) const final;

			/*! \brief update the thread view with the original data.
				\details This function shall only be called
					when it is save to access \p object
					without danger of race conditions, i.e.
					outside the game loop.
			*/
			void update() final;


			/// call this function from the client thread to trigger all delayed callbacks.
			void step() final;

			/// gets the mutex that protects the update step.
			std::mutex& getUpdateMutex() const final;

		private:
			IGameWorldView* mOriginal;

			// helper functions
			/// performs all cached step actions and clears cache
			void doStepActions();
			/// steps all game objects
			void doGOStep();

			//! list of all game object thread views for the original game objects.
			std::vector<std::shared_ptr<IViewThreadGameObject>> mGameObjects;

			using delayed_fun = std::function<void()>;
			//! function cached from within the game thread to be
			//! executed when the step function is called.
			std::vector<delayed_fun> mStepActions;

			/// delayed spawn listeners.
			ListenerList<IGameObjectView&> mSpawnListeners;
			/// reference to the spawn listener
			ListenerRef mSpawnListener;

			/// function to process the spawn of a new object.
			void onSpawn(IGameObjectView& object);

			/// mutex for the update process
			mutable std::mutex mUpdateMutex;

			/// mutex for delayed callback
			mutable std::mutex mStepActionMutex;
		};
	}
}

#endif // CVIEWTHREADGW_H_INCLUDED

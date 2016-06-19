#include "CViewThreadGW.h"
#include "CViewThreadGO.h"
#include <algorithm>
#include <iostream>

namespace game
{
namespace view_thread
{
	CViewThreadGameWorld::CViewThreadGameWorld(IGameWorldView& world) :
		mViewThreadId( std::this_thread::get_id() ) //world view is created in view thread
	{
		mSpawnListener = world.addSpawnListener([this](IGameObjectView& spawned) mutable { onSpawn(spawned); });
	}

	size_t CViewThreadGameWorld::object_count() const
	{
		return mGameObjects.size();
	}

	ListenerRef CViewThreadGameWorld::addSpawnListener(std::function<void(IGameObjectView&)>f)
	{
		CHECK_RAN_IN_VIEW_THREAD();
		return mSpawnListeners.addListener( f );
	}

	void CViewThreadGameWorld::iterateAllObjects(const std::function<void(IGameObjectView&)>& f) const
	{
		CHECK_RAN_IN_VIEW_THREAD();
		std::lock_guard<std::mutex> lock(mGameObjects_mutex);
		for(auto& object : mGameObjects)
			f(*object);
	}

	/*! \brief update the thread view with the original data.
		\details This function shall only be called
			when it is save to access \p object
			without danger of race conditions, i.e.
			outside the game loop.
	*/
	void CViewThreadGameWorld::update()
	{
		CHECK_RAN_IN_GAME_THREAD();
		std::lock_guard<std::mutex> lock(mGameObjects_mutex);

		// update all thread views
		for(auto& object : mGameObjects)
			object->update();
	}

	/// function to process the spawn of a new object.
	void CViewThreadGameWorld::onSpawn(IGameObjectView& object)
	{
		CHECK_RAN_IN_GAME_THREAD();

		// create new object ...
		auto spawned = std::make_shared<CViewThreadGameObject>(object);
		{
			// ... and add to mGameObjects.
			// extra scope to keep the lock as localized as possible
			std::lock_guard<std::mutex> lock(mGameObjects_mutex);
			mGameObjects.push_back( spawned );
		}


		std::lock_guard<std::mutex> lock(mStepAction_mutex);
		mStepActions.push_back([spawned, this]()
		{
			mSpawnListeners.notify(*spawned);
		});
	}

	/// gets the mutex that protects the update step.
	std::mutex& CViewThreadGameWorld::getUpdateMutex() const
	{
		return mGameObjects_mutex;
	}

	void CViewThreadGameWorld::doStepActions()
	{
		CHECK_RAN_IN_VIEW_THREAD();
		std::lock_guard<std::mutex> lock(mStepAction_mutex);
		for(auto& a : mStepActions)
			a();

		mStepActions.clear();
	}

	void CViewThreadGameWorld::doGOStep()
	{
		CHECK_RAN_IN_VIEW_THREAD();
		std::lock_guard<std::mutex> lock(mGameObjects_mutex);

		// remove objects that are no longer alive.
		// we need to do this here in the game thread, so that the objects
		// destructor is called in the game thread.
		auto nlast = std::remove_if(begin(mGameObjects), end(mGameObjects), [](const auto& o){ return !o->isAlive(); });
		mGameObjects.resize(std::distance(begin(mGameObjects), nlast));

		// step all game objects
		for(auto& obj : mGameObjects)
			obj->onStep();
	}

	void CViewThreadGameWorld::step()
	{
		CHECK_RAN_IN_VIEW_THREAD();
		// keeping this in function calls ensures minimal scope for the mutexes
		doStepActions();
		doGOStep();
	}

	void CViewThreadGameWorld::CHECK_RAN_IN_VIEW_THREAD() const
	{
        assert( std::this_thread::get_id() == mViewThreadId );
	}

	void CViewThreadGameWorld::CHECK_RAN_IN_GAME_THREAD() const
	{
        assert( std::this_thread::get_id() != mViewThreadId );
	}
}
}

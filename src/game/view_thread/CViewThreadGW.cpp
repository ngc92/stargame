#include "CViewThreadGW.h"
#include "CViewThreadGO.h"
#include <algorithm>
#include <iostream>

namespace game
{
namespace view_thread
{
	CViewThreadGameWorld::CViewThreadGameWorld(IGameWorldView& world)
	{
		mSpawnListener = world.addSpawnListener([this](IGameObjectView& spawned) mutable { onSpawn(spawned); });
	}

	size_t CViewThreadGameWorld::object_count() const
	{
		return mGameObjects.size();
	}

	ListenerRef CViewThreadGameWorld::addSpawnListener(std::function<void(IGameObjectView&)>f)
	{
		return mSpawnListeners.addListener( f );
	}

	void CViewThreadGameWorld::iterateAllObjects(const std::function<void(IGameObjectView&)>& f) const
	{
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
		std::lock_guard<std::mutex> lock(mUpdateMutex);

		// update all thread views
		for(auto& object : mGameObjects)
			object->update();
	}

	/// function to process the spawn of a new object.
	void CViewThreadGameWorld::onSpawn(IGameObjectView& object)
	{
		// this will never execute concurrently with update, so we can
		// do this.
		auto spawned = std::make_shared<CViewThreadGameObject>(object);
		mGameObjects.push_back( spawned );


		std::lock_guard<std::mutex> lock(mStepActionMutex);
		mStepActions.push_back([spawned, this]()
		{
			mSpawnListeners.notify(*spawned);
		});
	}

	/// gets the mutex that protects the update step.
	std::mutex& CViewThreadGameWorld::getUpdateMutex() const
	{
		return mUpdateMutex;
	}

	void CViewThreadGameWorld::doStepActions()
	{
		std::lock_guard<std::mutex> lock(mStepActionMutex);
		for(auto& a : mStepActions)
			a();

		mStepActions.clear();
	}

	void CViewThreadGameWorld::doGOStep()
	{
		std::lock_guard<std::mutex> lock(mUpdateMutex);

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
		// keeping this in function calls ensures minimal scope for the mutexes
		doStepActions();
		doGOStep();
	}

}
}

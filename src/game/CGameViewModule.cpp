#include "CGameViewModule.h"

namespace game 
{
	void CGameViewModule::step()
	{
		if(mStepMutex != nullptr)
		{
			std::lock_guard<std::mutex> lck(*mStepMutex);
			onStep();
		}
	}
	
	IGameWorldView& CGameViewModule::world()
	{
		return *mWorldView;
	}
	
	/// gives the world view to the module
	void CGameViewModule::setWorldView(IGameWorldView* worldview)
	{
		mWorldView = worldview;
	}
	
	void CGameViewModule::setStepMutex(std::mutex* mutex)
	{
		mStepMutex = mutex;
	}
}

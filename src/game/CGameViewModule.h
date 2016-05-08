#ifndef CGAMEVIEWMODULE_H_INCLUDED
#define CGAMEVIEWMODULE_H_INCLUDED

#include "IGameViewModule.h"

namespace game
{
	class CGameViewModule : public virtual IGameViewModule
	{
	public:
		virtual ~CGameViewModule() = default;
		
		/// this function should be called from the program main loop to
		/// let the module perform a step.
		void step() final;
		
		/// this function is called inside the game thread step function
		/// \attention Do not access variables of the module thread unprotected.
		void onGameStep(const IGameWorld& world) override {};
		
		/// sets the mutex that shall be used for step protection.
		void setStepMutex(std::mutex* mutex) final;
		
		/// gives the world view to the module
		void setWorldView(IGameWorldView* worldview) final;
	
	protected:
		IGameWorldView& world();
	
	private:
		/// function to be implemented, that does the actual step.
		virtual void onStep() = 0;
		
		std::mutex* mStepMutex = nullptr;
		IGameWorldView* mWorldView = nullptr;
	};
}

#endif // CGAMEVIEWMODULE_H_INCLUDED

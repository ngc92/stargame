#ifndef IGAMEVIEWMODULE_H_INCLUDED
#define IGAMEVIEWMODULE_H_INCLUDED

#include <mutex>
#include "fwd.h"

namespace game
{
	class IGameWorld;
	
	class IGameViewModule
	{
	public:
		virtual ~IGameViewModule() = default;
		
		/// this function should be called from the program main loop to
		/// let the module perform a step.
		virtual void step() = 0;
		
		/// this function is called after mutex and world have been set
		virtual void init() = 0;
		
		/// this function is called inside the game thread step function
		/// \attention Do not access variables of the module thread unprotected.
		virtual void onGameStep(const IGameWorld& world) = 0;
		
		/// sets the mutex that shall be used for step protection.
		virtual void setStepMutex(std::mutex* mutex) = 0;
		
		/// gives the world view to the module
		virtual void setWorldView(IGameWorldView* worldview) = 0;
	};
}
#endif // IGAMEVIEWMODULE_H_INCLUDED

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
		virtual void step( IGameWorldView& world_view ) = 0;

		/// this function is called after mutex and world have been set
		virtual void init( IGameWorldView& world_view ) = 0;
	};
}
#endif // IGAMEVIEWMODULE_H_INCLUDED

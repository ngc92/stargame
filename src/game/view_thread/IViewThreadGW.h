#ifndef IVIEWTHREADGW_H_INCLUDED
#define IVIEWTHREADGW_H_INCLUDED

#include "../IGameWorldView.h"
#include <mutex>

namespace game
{
	namespace view_thread
	{
		class IViewThreadGameWorld : public IGameWorldView
		{
		public:
			/*! \brief update the thread view with the original data.
				\details This function shall only be called
					when it is save to access \p object
					without danger of race conditions, i.e.
					outside the game loop.
			*/
			virtual void update() = 0;
			
			/// call this function from the client thread to trigger all delayed callbacks.
			virtual void step() = 0;
			
			/// gets the mutex that protects the update step.
			/// \todo here we need a multiple read/single write kind of mutex.
			virtual std::mutex& getUpdateMutex() const = 0;
		};
	}
}

#endif // IVIEWTHREADGW_H_INCLUDED

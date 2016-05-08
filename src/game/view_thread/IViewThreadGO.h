#ifndef IVIEWTHREADGOV_H_INCLUDED
#define IVIEWTHREADGOV_H_INCLUDED

#include "../IGameObjectView.h"

namespace game
{
	namespace view_thread
	{
		class IViewThreadGameObject : public IGameObjectView
		{
		public:
			/*! called inside the view thread to do the update
				step of the GameObjectView. From within this
				function, it is save to manipulate data
				within the view thread, but not the game thread.

				Calls the step listener.
			*/
			virtual void onStep() = 0;

			/*! \brief update the thread view with the original data.
				\details This function shall only be called
					when it is save to access \p object
					without danger of race conditions, i.e.
					outside the game loop.
			*/
			virtual void update() = 0;

			/// checks whether the referenced object is still alive.
			virtual bool isAlive() const = 0;

			/*! \brief Allows setting properties from view thread.
				\details This function caches assignments to properties
						from the view thread, which then are performed
						inside the game thread.
			*/
			virtual void setProperty( const std::string& path, const property::data_t& value) = 0;
		};
	}
}


#endif // IVIEWTHREADGOV_H_INCLUDED

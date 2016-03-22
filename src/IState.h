#ifndef ISTATE_H_INCLUDED
#define ISTATE_H_INCLUDED

#include <string>
#include "util.h"
#include <irrlicht/IEventReceiver.h>

/*! \class IState
    \brief Program state base class.
    \details An IState object defines the state the program can be in. Exactly one state has to be
            marked as the active state all the time. This is managed by the state manager (IStateManager class).
            A state can be identified by its name and an UUID.
*/
class IState : public noncopyable, ObjectCounter<IState>
{
	public:
		virtual ~IState() noexcept {};

		// callbacks
		/// if this state is active, update is called every frame.
		virtual void update() = 0;

		/// this is called after every drawing call has been made
		virtual void onDraw() = 0;

		/// called when the state becomes active
		virtual void onActivate() = 0;

		/// called when the state becomes inactive
		/// this function is not allowed to throw. If any problem occures while
		/// deactivating a state, logging an error is the preferred course of action.
		virtual void onDeactivate() noexcept = 0;

		/// gets the states name
		virtual const char* getName() const noexcept = 0;

		/// gets the GUI manager
		virtual IGUIEnvironment* getGUIEnvironment() noexcept = 0;

		/// a GUI event was detected, the current state has to process it.
		virtual bool onEvent(const irr::SEvent::SGUIEvent& event) = 0;

};


#endif // ISTATE_H_INCLUDED

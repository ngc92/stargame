#ifndef IEVENTLISTENER_H_INCLUDED
#define IEVENTLISTENER_H_INCLUDED

#include "util.h"
#include <irrlicht/Keycodes.h>
#include <irrlicht/IEventReceiver.h>

class IInputManager;

/*! \class IEventListener
	\brief Class that processes input events
	\details Instances of this class register at the global InputManager and get their respective methods called
				once an event happens. Currently, listening at mouse and key events is supported.
	\sa IInputManager
*/
class IEventListener : public ObjectCounter<IEventListener>
{
	public:
		/// d'tor
		virtual ~IEventListener() noexcept {};

		/// this function is called when this event listener is registered at the specified IInputManager.
		/// do not call this method from outside the InputManager
		virtual void registerListener( const IInputManager* mgr) = 0;

		/// \brief called upon keyboard event.
		/// \param key Key-Code of the pressed key
		/// \param press true, if key was pressed, false, if key was released.
		virtual void onKeyEvent(irr::EKEY_CODE key, bool press) = 0;

		/// \brief called upon mouse click
		/// \param button which button was pressed/released
		/// \param click whether the button was pressed or released
		/// \param x, y coordinates where the click happened.
		virtual void onMouseClickEvent(irr::E_MOUSE_BUTTON_STATE_MASK button, bool click, int x, int y) = 0;
};

#endif // IEVENTLISTENER_H_INCLUDED

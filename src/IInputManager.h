#ifndef IINPUTMANAGER_H_INCLUDED
#define IINPUTMANAGER_H_INCLUDED

#include <memory>
#include <irrlicht/Keycodes.h>
#include <irrlicht/vector2d.h>
#include <irrlicht/IEventReceiver.h>
#include "util.h"

class IEventListener;

/*! \class IInputManager
	\brief Receives all input and sends it to event listeners.
	\details This class gets all input events (i.e. all except gui events), caches event statuses
			(currently pressed keys, mouse position) and calls the respective methods of the
			registered event listeners.
	\todo ability to activate/deactivate event listeners.
*/
class IInputManager : 	public noncopyable,
						public ObjectCounter<IInputManager>

{
	public:
		/// virtual d'tor
		virtual ~IInputManager() noexcept {};

		// interface for receiving events
		/// called when a key is pressed/released.
		virtual void onKeyEvent( irr::EKEY_CODE key, bool press ) = 0;

		/// called when mouse click/release happens
		virtual void onMouseClickEvent( irr::E_MOUSE_BUTTON_STATE_MASK button, bool click, irr::s32 x, irr::s32 y ) = 0;

		/// called when mouse moves
		virtual void onMouseMoveEvent(irr::s32 x, irr::s32 y) = 0;

		// input status queries

		/// returns whether the key \p key is currently pressed down.
		virtual bool isKeyDown( irr::EKEY_CODE key ) const = 0;

		/// gets the current mouse position
		virtual screen_vector getMousePosition() const = 0;

		/// gets whether the mouse button \p button is currently pressed down.
		virtual bool isMouseButtonPressed(irr::E_MOUSE_BUTTON_STATE_MASK button) const = 0;


		// ingame controls better use event listeners
		/// register an event listener. every registered event listener gets called the respective
		/// methods when a event method is called here.
		virtual void addEventListener(std::shared_ptr<IEventListener> listener) = 0;

		/// removes an registered event listener.
		virtual void removeEventListener(const IEventListener* listener) = 0;
};


#endif // IINPUTMANAGER_H_INCLUDED

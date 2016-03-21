#ifndef CINPUTMANAGER_H_INCLUDED
#define CINPUTMANAGER_H_INCLUDED

#include "IInputManager.h"
#include <vector>
#include <array>

/// standard implementation of IInputManager
class CInputManager : public IInputManager
{
	public:
		// ctor/dtor
		CInputManager();

		~CInputManager() noexcept override {};

		// receive events
		void onKeyEvent( irr::EKEY_CODE key, bool press ) override;

		void onMouseClickEvent( irr::E_MOUSE_BUTTON_STATE_MASK button, bool click, irr::s32 x, irr::s32 y ) override;

		void onMouseMoveEvent(irr::s32 x, irr::s32 y) override;

		// check event status
		bool isKeyDown( irr::EKEY_CODE key ) const override;

		screen_vector getMousePosition() const override;

		bool isMouseButtonPressed(irr::E_MOUSE_BUTTON_STATE_MASK button) const override;


		// event listeners
		void addEventListener(std::shared_ptr<IEventListener> listener) override;

		void removeEventListener(const IEventListener* listener) override;

	private:
		/// this array caches which keys are currently pressed
		std::array<bool, 255> mKeyStates;
		/// bitfield for pressed mouse buttons
		unsigned char mMouseButtonStates;
		/// current mouse position
		screen_vector mMousePosition;

		// event listeners
		typedef std::vector<std::shared_ptr<IEventListener>> listener_container_type;

		/// vector containing all registered event listeners
		listener_container_type mListeners;
};

#endif // CINPUTMANAGER_H_INCLUDED

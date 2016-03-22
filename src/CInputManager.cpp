#include "CInputManager.h"
#include "IEventListener.h"
#include <cassert>

CInputManager::CInputManager() : mMouseButtonStates(0)
{
	for(unsigned int i = 0; i < mKeyStates.size(); ++i)
	{
		mKeyStates[i] = 0;
	}
}

void CInputManager::onKeyEvent( irr::EKEY_CODE key, bool press )
{
	//assert(mKeyStates[key] != press);
	mKeyStates[key] = press;
	for(auto i = mListeners.begin(); i != mListeners.end(); ++i)
	{
		(*i)->onKeyEvent(key, press);
	}
}

void CInputManager::onMouseClickEvent( irr::E_MOUSE_BUTTON_STATE_MASK button, bool click, irr::s32 x, irr::s32 y )
{
	if(click)
		mMouseButtonStates |= button;
	else
		mMouseButtonStates &= ~button;

	for(auto i = mListeners.begin(); i != mListeners.end(); ++i)
	{
		(*i)->onMouseClickEvent(button, click, x, y);
	}
}

void CInputManager::onMouseMoveEvent(irr::s32 x, irr::s32 y)
{
	mMousePosition.X = x;
	mMousePosition.Y = y;
}

bool CInputManager::isKeyDown( irr::EKEY_CODE key ) const
{
	return mKeyStates[key];
}

screen_vector CInputManager::getMousePosition() const
{
	return mMousePosition;
}

bool CInputManager::isMouseButtonPressed(irr::E_MOUSE_BUTTON_STATE_MASK button) const
{
	return mMouseButtonStates & button;
}

void CInputManager::addEventListener(std::shared_ptr<IEventListener> listener)
{
	// register
	listener->registerListener(this);
	// and add to registered listeners
	mListeners.push_back(listener);
}

void CInputManager::removeEventListener(const IEventListener* listener)
{
	auto iter = std::find_if( mListeners.begin(), mListeners.end(), [listener](const std::shared_ptr<IEventListener>& i)
																		{ return i.get() == listener ;});
	if ( iter == mListeners.end() )
		BOOST_THROW_EXCEPTION( std::runtime_error(" Trying to remove unregistered event listener"));

	mListeners.erase( iter );
}

#include "CIrrMasterEventReceiver.h"
#include "IInputManager.h"
#include "IStateManager.h"
#include <irrlicht/IGUIElement.h>
#include <irrlicht/IrrlichtDevice.h>
#include <irrlicht/IGUIEnvironment.h>
#include <boost/exception/diagnostic_information.hpp>
#include <iostream>

CIrrMasterEventReceiver::CIrrMasterEventReceiver(IInputManager* ipmgr,
												IStateManager* statemgr) :
			mInputManager(ipmgr),
			mStateManager(statemgr),
			mDevice(nullptr)
{

}

void CIrrMasterEventReceiver::setDevice(irr::IrrlichtDevice* dev)
{
	mDevice = dev;
	mDevice->setEventReceiver(this);
}

bool CIrrMasterEventReceiver::OnEvent(const irr::SEvent& event)
{
	try
	{
		return dispenseEvent(event);
	}
	 catch( std::exception& ex )
	{
		LOG_WARNING(ELogCategory::ELC_IRRLICHT, boost::diagnostic_information(ex));
		return false;
	}
}

bool CIrrMasterEventReceiver::dispenseEvent(const irr::SEvent& event)
{
	switch(event.EventType)
	{
		case irr::EET_KEY_INPUT_EVENT:
		{
			if( !mDevice->getGUIEnvironment()->postEventFromUser(event) )
			{
			mInputManager->onKeyEvent(event.KeyInput.Key, event.KeyInput.PressedDown);
			}
			return false;
		}
		break;
		case irr::EET_MOUSE_INPUT_EVENT:
		{
			/// \todo there should be a better way of of separating game from ui input
			if( !mDevice->getGUIEnvironment()->postEventFromUser(event) )
			{
			// dissect mouse event and call the corresponding function
			switch(event.MouseInput.Event)
			{
				case irr::EMIE_LMOUSE_PRESSED_DOWN:
					mInputManager->onMouseClickEvent(irr::EMBSM_LEFT, true, event.MouseInput.X, event.MouseInput.Y);
					break;
				case irr::EMIE_RMOUSE_PRESSED_DOWN:
					mInputManager->onMouseClickEvent(irr::EMBSM_RIGHT, true, event.MouseInput.X, event.MouseInput.Y);
					break;
				case irr::EMIE_MMOUSE_PRESSED_DOWN:
					mInputManager->onMouseClickEvent(irr::EMBSM_MIDDLE, true, event.MouseInput.X, event.MouseInput.Y);
					break;
				case irr::EMIE_LMOUSE_LEFT_UP:
					mInputManager->onMouseClickEvent(irr::EMBSM_LEFT, false, event.MouseInput.X, event.MouseInput.Y);
					break;
				case irr::EMIE_RMOUSE_LEFT_UP:
					mInputManager->onMouseClickEvent(irr::EMBSM_RIGHT, false, event.MouseInput.X, event.MouseInput.Y);
					break;
				case irr::EMIE_MMOUSE_LEFT_UP:
					mInputManager->onMouseClickEvent(irr::EMBSM_MIDDLE, false, event.MouseInput.X, event.MouseInput.Y);
					break;
				case irr::EMIE_MOUSE_MOVED:
					mInputManager->onMouseMoveEvent(event.MouseInput.X, event.MouseInput.Y);
					break;
			};
			}

			return false;
		}
		break;
		case irr::EET_LOG_TEXT_EVENT:
		{
			LOG_MESSAGE(ELogCategory::ELC_IRRLICHT, event.LogEvent.Text);
			return true;
		}
		break;
		case irr::EET_GUI_EVENT:
		{
			return mStateManager->onEvent(event.GUIEvent);
		}
		break;

	}

	return false;
}

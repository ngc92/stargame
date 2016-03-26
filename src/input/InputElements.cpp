#include "InputElements.h"

namespace input
{
	CInputButton::CInputButton(std::string name, float value) :
		CInputElement(name, value)
	{
	}

	void CInputButton::press()
	{
		std::lock_guard<std::mutex> lck(mMutex);
		mPressed = true;
	}

	float CInputButton::getNewValue()
	{
		float val = mPressed ? 1 : 0;
		mPressed = false;
		return val;
	}

	// --------------------------------------------------------

	CInputSwitch::CInputSwitch(std::string name, float value) :
		CInputElement(name, value)
	{
	}

	void CInputSwitch::setSwitch( bool b )
	{
		std::lock_guard<std::mutex> lck(mMutex);
		mSwitch = b;
	}

	float CInputSwitch::getNewValue()
	{
		return mSwitch ? 1 : 0;
	}

	// --------------------------------------------------------

	CInputGauge::CInputGauge(std::string name, float value) :
		CInputElement(name, value)
	{
	}

	void CInputGauge::setGauge( float f )
	{
		std::lock_guard<std::mutex> lck(mMutex);
		mGauge = f;
	}

	float CInputGauge::getNewValue()
	{
		return mGauge;
	}

	// --------------------------------------------------------
	// factory function
	 std::shared_ptr<IInputElement> createInputElement( std::string name, InputType type, float init )
	 {
        switch(type)
        {
		case InputType::BUTTON:
			return std::make_shared<CInputButton>(std::move(name), init);
			break;
		case InputType::SWITCH:
			return std::make_shared<CInputSwitch>(std::move(name), init);
			break;
		case InputType::GAUGE:
			return std::make_shared<CInputGauge>(std::move(name), init);
			break;
        }
	 }
}

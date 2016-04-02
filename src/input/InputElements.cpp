#include "InputElements.h"

namespace input
{
	CInputButton::CInputButton(std::string name, float value) :
		CInputElement(name, value)
	{
	}

	float CInputButton::getNewValue()
	{
		float val = mPressed ? 1 : 0;
		mPressed = false;
		return val;
	}

	InputType CInputButton::type() const
	{
		return InputType::BUTTON;
	}

	void CInputButton::increase()
	{
		std::lock_guard<std::mutex> lck(mMutex);
		mPressed = true;
	}

	void CInputButton::decrease()
	{

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

	InputType CInputSwitch::type() const
	{
		return InputType::SWITCH;
	}

	void CInputSwitch::increase()
	{
		setSwitch(true);
	}

	void CInputSwitch::decrease()
	{
		setSwitch(false);
	}

	// --------------------------------------------------------

	CInputGauge::CInputGauge(std::string name, float value) :
		CInputElement(name, value)
	{
	}

	void CInputGauge::changeGauge( float change )
	{
		std::lock_guard<std::mutex> lck(mMutex);
		mGauge += change;
	}

	float CInputGauge::getNewValue()
	{
		return mGauge;
	}

	InputType CInputGauge::type() const
	{
		return InputType::GAUGE;
	}

	void CInputGauge::increase()
	{
		changeGauge(0.1);
	}

	void CInputGauge::decrease()
	{
		changeGauge(-0.1);
	}

	// --------------------------------------------------------
	// 						factory function
	// --------------------------------------------------------
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

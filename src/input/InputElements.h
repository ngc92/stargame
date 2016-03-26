#ifndef INPUTELEMENTS_H_INCLUDED
#define INPUTELEMENTS_H_INCLUDED

#include "CInputElement.h"

namespace input
{
	// these inheritances are fine, because
	class CInputButton : public CInputElement, public IInputButton
	{
	public:
		CInputButton(std::string name, float value = 0);
		void press() override;
	private:
		float getNewValue() override;
		bool mPressed;
	};

	class CInputSwitch : public CInputElement, public IInputSwitch
	{
	public:
		CInputSwitch(std::string name, float value = 0);
		void setSwitch( bool state ) override;
	private:
		float getNewValue() override;
		bool mSwitch;
	};

	class CInputGauge : public CInputElement, public IInputGauge
	{
	public:
		CInputGauge(std::string name, float value = 0);
		void setGauge( float value ) override;
	private:
		float getNewValue() override;
		float mGauge;
	};
}

#endif // INPUTELEMENTS_H_INCLUDED

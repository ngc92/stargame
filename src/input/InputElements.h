#ifndef INPUTELEMENTS_H_INCLUDED
#define INPUTELEMENTS_H_INCLUDED

#include "CInputElement.h"

namespace input
{
	// these inheritances are fine, because
	class CInputButton final : public CInputElement
	{
	public:
		CInputButton(std::string name, float value = 0);

		InputType type() const override;
		void increase() override;
		void decrease() override;
	private:
		float getNewValue() override;
		bool mPressed;
	};

	class CInputSwitch : public CInputElement
	{
	public:
		CInputSwitch(std::string name, float value = 0);
		void setSwitch( bool state );

		InputType type() const override;
		void increase() override;
		void decrease() override;
	private:
		float getNewValue() override;
		bool mSwitch;
	};

	class CInputGauge : public CInputElement
	{
	public:
		CInputGauge(std::string name, float value = 0);

		void changeGauge( float change );

		InputType type() const override;
		void increase() override;
		void decrease() override;

	private:
		float getNewValue() override;
		float mGauge;
	};
}

#endif // INPUTELEMENTS_H_INCLUDED

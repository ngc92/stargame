#ifndef CINPUTBUTTON_H_INCLUDED
#define CINPUTBUTTON_H_INCLUDED

#include <map>
#include "CInputElement.h"

namespace input
{
	class CInputButton : public CInputElement
	{
	public:
		CInputButton(std::string path, float default_value);
		
		void addButtonState( int key, float value );

		InputType type() const override;
		void onKeyEvent( int key_code, KeyState state ) override;
		std::function<void(game::IGameObject&)> onStep() override;

	private:
		float mDefaultValue;
		std::map<int, float> mButtonStates;
		std::map<int, bool> mKeyStates;
	};
}

#endif // CINPUTBUTTON_H_INCLUDED

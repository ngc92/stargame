#include "CInputButton.h"

namespace input
{
	CInputButton::CInputButton(std::string path, game::view_thread::IViewThreadGameObject* obj,
							float def_value) :
		CInputElement( std::move(path), obj ), mDefaultValue(def_value)
	{
	}

	InputType CInputButton::type() const
	{
		return InputType::BUTTON;
	}

	void CInputButton::addButtonState( int key, float value )
	{
		mButtonStates[key] = value;
	}

	void CInputButton::onStep()
	{
		// count active button states
		int ctr = 0;
		int active = -1;
		for(const auto& v : mKeyStates)
		{
			ctr += v.second ? 1 : 0;
			if(v.second) active = v.first;
		}
		if(ctr != 1)
		{
			setValue( mDefaultValue );
		} else {
			setValue( mButtonStates.at( active ) );
		}
	}

	void CInputButton::onKeyEvent( int key_code, KeyState state )
	{
		auto key = mButtonStates.find(key_code);
		if(key != mButtonStates.end())
		{
			mKeyStates[key->first] = (state == KeyState::PRESSED);
		}

	}
}

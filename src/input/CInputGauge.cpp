#include "CInputGauge.h"


namespace input
{
	CInputGauge::CInputGauge(std::string path, game::view_thread::IViewThreadGameObject* obj, 
							int inc, int dec, float mn, float mx) :
		CInputElement( std::move(path), obj ),
		mIncreaseKey(inc), mDecreaseKey(dec),
		mMinimumValue(mn), mMaximumValue(mx)
	{
	}

	InputType CInputGauge::type() const
	{
		return InputType::GAUGE;
	}
	
	void CInputGauge::onStep()
	{
		/// \todo actual increase/decrease function.
		if(mIncreasePressed)
		{
			setValue( mMaximumValue );
		} 
		else if(mDecreasePressed)
		{
			setValue( mMinimumValue );
		}
	}

	void CInputGauge::onKeyEvent( int key_code, KeyState state )
	{
		if(key_code == mIncreaseKey )
		{
			mIncreasePressed = state == KeyState::PRESSED;
		}
		if(key_code == mDecreaseKey )
		{
			mDecreasePressed = state == KeyState::PRESSED;
		}
		
	}
}

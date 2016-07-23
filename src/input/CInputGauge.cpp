#include "CInputGauge.h"


namespace input
{
	CInputGauge::CInputGauge(std::string path, int inc, int dec, float mn, float mx) :
		CInputElement( std::move(path) ),
		mIncreaseKey(inc), mDecreaseKey(dec),
		mMinimumValue(mn), mMaximumValue(mx)
	{
	}

	InputType CInputGauge::type() const
	{
		return InputType::GAUGE;
	}
	
	std::function<void(game::IGameObject&)> CInputGauge::onStep()
	{
		/// \todo actual increase/decrease function.
		if(mIncreasePressed)
		{
			return setValue( mMaximumValue );
		} 
		else if(mDecreasePressed)
		{
			return setValue( mMinimumValue );
		}
		
		return std::function<void(game::IGameObject&)>();
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

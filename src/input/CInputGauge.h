#ifndef CINPUTGAUGE_H_INCLUDED
#define CINPUTGAUGE_H_INCLUDED

#include "CInputElement.h"

namespace input
{
	class CInputGauge : public CInputElement
	{
	public:
		CInputGauge(std::string path, game::view_thread::IViewThreadGameObject*, 
					int inc, int dec, float mn, float mx);

		InputType type() const override;
		void onKeyEvent( int key_code, KeyState state ) override;
		void onStep() override;

	private:
		int mIncreaseKey = -1;
		int mDecreaseKey = -1;
		
		bool mIncreasePressed = false;
		bool mDecreasePressed = false;
		
		float mMinimumValue = 0;
		float mMaximumValue = 1;
	};
}

#endif // CINPUTGAUGE_H_INCLUDED

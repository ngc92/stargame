#include "CInputElement.h"

namespace input
{
	CInputElement::CInputElement(std::string name, float value) :
		mName(name), mValue(value)
	{

	}

	float CInputElement::value() const
	{
		return mValue;
	}

	const std::string& CInputElement::name() const
	{
		return mName;
	}

	void CInputElement::update()
	{
		std::lock_guard<std::mutex> lck( mMutex );
		mValue = getNewValue();
	}
}

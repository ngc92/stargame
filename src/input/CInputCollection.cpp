#include "CInputCollection.h"

namespace input
{
    void CInputCollection::addInputElement(std::weak_ptr<IInputElement> element)
    {
		mElements.push_back(std::move(element));
    }

    void CInputCollection::iterateInputs(std::function<void(std::weak_ptr<IInputElement>&)> f) const
    {
		for(auto el : mElements)
			f(el);
    }
}

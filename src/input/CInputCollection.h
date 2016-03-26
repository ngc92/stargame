#ifndef CINPUTCOLLECTION_H_INCLUDED
#define CINPUTCOLLECTION_H_INCLUDED

#include "IInputCollection.h"
#include <vector>

namespace input
{
	class CInputCollection : public IInputCollection
	{
	public:
		void addInputElement(std::weak_ptr<IInputElement> element) override;
		void iterateInputs(std::function<void(std::weak_ptr<IInputElement>&)> f) const override;
	private:
		std::vector<std::weak_ptr<IInputElement>> mElements;
	};
}

#endif // CINPUTCOLLECTION_H_INCLUDED

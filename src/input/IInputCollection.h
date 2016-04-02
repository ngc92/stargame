#ifndef ICONTROLLABLEOBJECT_H_INCLUDED
#define ICONTROLLABLEOBJECT_H_INCLUDED

#include <functional>
#include <memory>

namespace input
{
	class IInputElement;

	class IInputCollection
	{
	public:
		virtual ~IInputCollection() = default;
		virtual void addInputElement(std::weak_ptr<IInputElement> element) = 0;
		virtual void iterateInputs(std::function<void(std::weak_ptr<IInputElement>&)> f) const = 0;
	};
}

#endif // ICONTROLLABLEOBJECT_H_INCLUDED

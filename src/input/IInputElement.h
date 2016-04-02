#ifndef IINPUTELEMENT_H_INCLUDED
#define IINPUTELEMENT_H_INCLUDED

#include "util.h"
#include <string>

namespace input
{

	enum class InputType
	{
		BUTTON,			//!< single impulses
		SWITCH,			//!< set to on/off state an stay there
		GAUGE			//!< set to a value in [0,1]
	};

	class IInputElement : public noncopyable
	{
	public:
		virtual ~IInputElement() = default;
		virtual float value() const = 0;
		virtual void update() = 0;
		virtual const std::string& name() const = 0;
		virtual InputType type() const = 0;

		// set input
		virtual void increase() = 0;
		virtual void decrease() = 0;
	};

	// factory function
	std::shared_ptr<IInputElement> createInputElement( std::string name, InputType type, float init );
}

#endif // IINPUTELEMENT_H_INCLUDED

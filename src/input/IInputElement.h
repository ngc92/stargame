#ifndef IINPUTELEMENT_H_INCLUDED
#define IINPUTELEMENT_H_INCLUDED

#include "util.h"
#include <string>
#include <boost/property_tree/ptree_fwd.hpp>

namespace property
{
	class IPropertyObjectView;
	class IPropertyView;
}

namespace game
{
	class IGameObject;
}

namespace input
{

	enum class InputType
	{
		BUTTON,			//!< single impulses
		SWITCH,			//!< set to on/off state an stay there
		GAUGE			//!< set to a value in [0,1]
	};

	enum class KeyState
	{
		PRESSED,
		RELEASED
	};

	/*! \class IInputElement
		\brief Base class for something that can receive inputs.
		\details This class provides an interface that allows the thread-save
				transfer of inputs from the user into the game thread.
		\todo check the threading model and write documentation!
	*/
	class IInputElement : public noncopyable
	{
	public:
		virtual ~IInputElement() = default;
		virtual InputType type() const = 0;

		virtual void onKeyEvent( int key_code, KeyState state ) = 0;
		virtual std::function<void(game::IGameObject&)> onStep() = 0;
	};
}

#endif // IINPUTELEMENT_H_INCLUDED

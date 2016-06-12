#ifndef IINPUTCONFIGURATION_H_INCLUDED
#define IINPUTCONFIGURATION_H_INCLUDED

#include <irrlicht/Keycodes.h>
#include <string>
#include <memory>

namespace property
{
	class IPropertyView;
}

namespace input
{
	class IInputElement;

	enum class KeyAction : int
	{
		PRESS, RELEASE, HOLD
	};

	struct InputAction
	{
		irr::EKEY_CODE key;
		KeyAction action;
	};

	class IInputConfig
	{
	public:
		virtual ~IInputConfig() = default;
		virtual void load() = 0;

		/// creates an input element that manipulates \p property, if specified.
		/// \return pointer to the newly created input element, or nullptr if none could be created.
		virtual std::shared_ptr<IInputElement> getInputElemt( const property::IPropertyView& property ) = 0;
	};
}

#endif // IINPUTCONFIGURATION_H_INCLUDED

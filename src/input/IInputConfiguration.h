#ifndef IINPUTCONFIGURATION_H_INCLUDED
#define IINPUTCONFIGURATION_H_INCLUDED

#include <irrlicht/Keycodes.h>
#include <string>

namespace input
{
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
		/// \param increase: get increase or decrease match?
		virtual InputAction findMatch( const std::string& input, bool increase ) = 0;
	};
}

#endif // IINPUTCONFIGURATION_H_INCLUDED

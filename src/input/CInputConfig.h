#ifndef CINPUTCONFIG_H_INCLUDED
#define CINPUTCONFIG_H_INCLUDED

#include "IInputConfiguration.h"
#include <vector>

namespace input
{
	struct KeyInputRule
	{
        irr::EKEY_CODE key;
        std::string pattern;
        KeyAction action;
        bool increase;
	};

	class CInputConfig : public IInputConfig
	{
	public:
		void load() override;
		InputAction findMatch( const std::string& input, bool increase ) override;
	private:
		std::vector<KeyInputRule> mMappingRules;
	};
}

#endif // CINPUTCONFIG_H_INCLUDED

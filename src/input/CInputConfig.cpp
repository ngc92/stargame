#include "CInputConfig.h"
#include <regex>
#include <cassert>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace input
{
	void CInputConfig::load()
	{
		using namespace boost::property_tree;
		ptree tree;
		read_xml("input.xml", tree);
		for(auto& rule : tree)
		{
			assert(rule.first == "rule");
			std::string pattern = rule.second.get<std::string>("pattern");
			std::size_t key = rule.second.get<int>("key");
			std::string action = rule.second.get<std::string>("action");
			KeyAction act;
			if(action == "press")		 { act = KeyAction::PRESS; }
			else if(action == "release") { act = KeyAction::RELEASE; }
			else if(action == "hold")	 { act = KeyAction::HOLD; }
			else {assert(0);}
			bool inc = rule.second.get<bool>("increase");

			mMappingRules.push_back(KeyInputRule{(irr::EKEY_CODE)key, pattern, act, inc});
		}
	}

	InputAction CInputConfig::findMatch( const std::string& input, bool increase )
	{
        for( const auto& rule : mMappingRules )
		{
            if( std::regex_match(input, std::regex(rule.pattern)) && rule.increase == increase )
			{
				return InputAction{rule.key, rule.action};
			}
		}

		///  \todo what do we do in case of mutliple/no matches?
		assert(0);
	}
}

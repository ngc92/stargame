#include "CInputConfig.h"
#include <regex>
#include <cassert>
#include <iostream>
#include <boost/property_tree/xml_parser.hpp>

#include "util.h"
#include "IInputElement.h"
#include "property/IProperty.h"
#include "InputElements.h"


namespace input
{
	CInputConfig::CInputConfig()
	{

	}
	CInputConfig::~CInputConfig()
	{

	}

	void CInputConfig::load()
	{
		using namespace boost::property_tree;
		ptree tree;
		read_xml("input.xml", tree);
		for(auto& rule : tree)
		{
			assert(rule.first == "rule");
			std::string pattern = rule.second.get<std::string>("pattern");
			mMappingRules[pattern] = make_unique<ptree>( rule.second );
		}
	}

	std::shared_ptr<IInputElement> CInputConfig::getInputElemt( const property::IPropertyView& property )
	{
		std::string input = property.path();
        for( const auto& rule : mMappingRules )
		{
			const std::string& pattern = rule.first;
            if( std::regex_match(input, std::regex(pattern)))
			{
				return createInputElement( *rule.second, property );
			}
		}

		return nullptr;
	}
}

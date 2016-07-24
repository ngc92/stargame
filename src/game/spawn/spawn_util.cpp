#include "spawn_util.h"
#include <boost/property_tree/ptree.hpp>
#include <regex>
#include "property/CPropertyObject.h"
#include "consts.h"

namespace game
{
namespace spawn
{
	// helpers

	b2Vec2 read_position( const boost::property_tree::ptree& tree )
	{
		return b2Vec2{tree.get<float>("x"), tree.get<float>("y")};
	}

	b2Vec2 read_position( const boost::property_tree::ptree& tree, const vertex_cache_t& vcache  )
	{
		auto vname = tree.get_value<std::string>();
		if( vname != "" )
		{
			return vcache.at(vname);
		}
		else
		{
			return read_position(tree);
		}
	}

	std::shared_ptr<property::IPropertyObject> make_property_object( std::string name )
	{
		return std::make_shared<property::CPropertyObject>(std::move(name));
	}

	property::data_t get_prop_value( const boost::property_tree::ptree& props )
	{
		const std::string& s = props.get_value<std::string>();
		// check if number
		if(std::regex_match(s, std::regex("-?[0-9]+([.][0-9]+)?")))
		{
			return props.get_value<float>();
		} else {
			return s;
		}
	}
}
}

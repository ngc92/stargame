#ifndef SPAWN_UTIL_H_INCLUDED
#define SPAWN_UTIL_H_INCLUDED

#include <unordered_map>
#include <boost/property_tree/ptree.hpp>
#include "game/fwd.h"
#include "property/property.h"

class b2Vec2;

namespace game
{
	namespace spawn
	{
		using vertex_cache_t = std::unordered_map<std::string, b2Vec2>;

		b2Vec2 read_position( const boost::property_tree::ptree& tree );
		b2Vec2 read_position( const boost::property_tree::ptree& tree, const vertex_cache_t& vcache  );

		std::shared_ptr<property::IPropertyObject> make_property_object( std::string name );

		property::data_t get_prop_value( const boost::property_tree::ptree& props );
	}
}

#endif // SPAWN_UTIL_H_INCLUDED

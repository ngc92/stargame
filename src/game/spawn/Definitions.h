#ifndef COMPONENTDEFINITION_H_INCLUDED
#define COMPONENTDEFINITION_H_INCLUDED

#include <vector>
#include <unordered_map>
#include <boost/property_tree/ptree_fwd.hpp>
#include "game/fwd.h"

class b2Vec2;

namespace property
{
	class IPropertyObject;
}

namespace game
{
namespace spawn
{
	using vertex_cache_t = std::unordered_map<std::string, b2Vec2>;

}
}

#endif // COMPONENTDEFINITION_H_INCLUDED

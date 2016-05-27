#include "SShip.h"
#include "spawn_util.h"

#include "property/IPropertyObject.h"
#include "property/CProperty.h"

namespace game
{
namespace spawn
{
	SShip::SShip(const boost::property_tree::ptree& props):
		mHull( props.get<std::string>("hull") ),
		mName( props.get<std::string>("name") )
	{
		auto comps = props.get_child("components");
		for(auto& comp : comps )
		{
			assert(comp.first == "component");
			std::string type = comp.second.get<std::string>("type");
			int cell = comp.second.get<int>("cell");
			mComponents.push_back( {std::move(type), cell} );
		}

		auto attribs = props.get_child("attributes");
		for(auto& attr : attribs)
		{
			mAttributes.insert( {attr.first, attr.second.get_value<std::string>()} );
		}
	}

	const std::string& SShip::hull() const
	{
		return mHull;
	}

	const std::string& SShip::name() const
	{
		return mName;
	}

	auto SShip::components() const -> const cmp_vec_t&
	{
		return mComponents;
	}

	void SShip::addAttributes( property::IPropertyObject& obj ) const
	{
		for(auto& attrib : mAttributes)
		{
			obj.addProperty( property::CProperty::create(attrib.first, &obj, attrib.second) );
		}
	}

}
}

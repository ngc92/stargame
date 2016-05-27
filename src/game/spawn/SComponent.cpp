#include "SComponent.h"
#include "spawn_util.h"

#include "property/CProperty.h"
#include <iostream>

#include "consts.h"
#include "factory.h"
#include "game/object_module/components/IComponent.h"

namespace game
{
namespace spawn
{
	// ------------------------------------------------------------

	SComponent::SComponent(const boost::property_tree::ptree& props) :
		mType( props.get<std::string>("type") ),
		mHitPoints( props.get<float>("HP") ),
		mWeight( props.get<float>("weight")),
		mProperties( make_property_object( "data" ) )
	{
		auto subs = props.get_child("properties");
		for(auto& data : subs )
		{
			mProperties->addProperty( property::CProperty::create(data.first, mProperties.get(), get_prop_value(data.second) ) );
		}
	}


	const std::string& SComponent::type() const
	{
		return mType;
	}

	float SComponent::HP() const
	{
		return mHitPoints;
	}

	float SComponent::weight() const
	{
		return mWeight;
	}

	const property::IPropertyObject& SComponent::getProperties() const
	{
		return *mProperties;
	}

	std::shared_ptr<IComponent> SComponent::create() const
	{
		std::shared_ptr<components::IComponent> component = constructComponent(type());

		// set hitpoints, maxHP and weight
		component->setHitPoints( HP(), HP() );
		component->setWeight( weight() );

		// set other attributes
		mProperties->forallProperties(
			[&component](property::IPropertyView& prop)
			{
				*component->getPropertyPtr(prop.name()) = prop.value();
			}
		);

		return component;
	}

}
}

#include "SpawnEvent.h"
#include "property/CPropertyObject.h"
#include "property/CProperty.h"
#include "game/IGameObjectView.h"

namespace game
{
namespace view_thread
{
	// helper function to copy properties
	void copyProperties(property::IPropertyObject& target, const property::IPropertyObjectView& source)
	{
		source.forallProperties([&](property::IPropertyView& view) mutable
		{
			auto newprop = property::CProperty::create( view.name(), &target, view.value() );
		}, false);

		// copy all children
		source.forallChildren([&](const property::IPropertyObjectView& view) mutable
		{
			auto child = std::make_shared<property::CPropertyObject>( view.name() );
			target.addChild( child );
			copyProperties(*child, view);
		});
	}

	SpawnEvent::SpawnEvent( IGameObjectView& spawned ) :
		mProperties( std::make_shared<property::CPropertyObject>("spawn_event") )
	{
		// copy all properties from original into here
		copyProperties(*mProperties, spawned);
	}

	const property::IPropertyObject& SpawnEvent::properties() const
	{
		return *mProperties;
	}
}
}

#include "UpdateEvent.h"
#include "property/CPropertyObject.h"
#include "property/CProperty.h"
#include "game/IGameObjectView.h"

namespace game
{
namespace threading
{
	SpawnEvent::SpawnEvent( IGameObjectView& spawned ) :
		mProperties( std::make_shared<property::CPropertyObject>("spawn_event") ),
		mSpawnData( spawned )
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

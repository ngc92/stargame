#include "TacticalMapCtrl.h"
#include "ITacticalMapView.h"
#include "ITacticalMapIcon.h"
#include "game/IGameWorldView.h"
#include "game/IGameObjectView.h"
#include <iostream>

namespace graphic
{
	TacticalMapCtrl::TacticalMapCtrl(ITacticalMapView* view, game::IGameWorldView& world) : mView(view)
	{
		using std::placeholders::_1;
		mSpawnListener = world.addSpawnListener(std::bind(addObject, this, _1));
		world.iterateAllObjects(std::bind(addObject, this, _1));
	}

	TacticalMapCtrl::~TacticalMapCtrl()
	{
	}

	void TacticalMapCtrl::addObject( game::IGameObjectView& object )
	{
		/// \todo determine, whether to show this object on the tactical map.
        /// for now, show all!
        auto view_entity = mView->addObject( object.position(), object.angle(), 0, object.name() );
        auto update = object.addStepListener([view_entity, &object]()
											{
												view_entity->setPosition( object.position() );
												view_entity->setAngle( object.angle() );
											 });

		mRegisteredListeners[&object] = std::move(update);
	}
}

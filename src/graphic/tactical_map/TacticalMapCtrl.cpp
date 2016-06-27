#include "TacticalMapCtrl.h"
#include "ITacticalMapView.h"
#include "ITacticalMapIcon.h"
#include "game/IGameWorldView.h"
#include "game/IGameObjectView.h"
#include <iostream>
#include <functional>

namespace graphic
{
	TacticalMapCtrl::TacticalMapCtrl(ITacticalMapView* view, game::IGameWorldView& world) : mView(view)
	{
		using namespace std::placeholders;
		mSpawnListener = world.addSpawnListener(std::bind(&TacticalMapCtrl::addObject, this, _1));
		world.iterateAllObjects(std::bind(&TacticalMapCtrl::addObject, this, _1));
	}

	TacticalMapCtrl::~TacticalMapCtrl()
	{
	}

	void TacticalMapCtrl::addObject( game::IGameObjectView& object )
	{
		/// \todo determine, whether to show this object on the tactical map.
		/// for now, show all!
		auto type = object.category();
		auto team = boost::get<int>(object.getProperty("affiliation.team").value());

		// filter types
		if( type == game::ObjectCategory::BULLET)
			return;

		auto view_entity = mView->addObject( object.position(), object.angle(), team, "ship" );
		auto update = object.addStepListener([view_entity, &object]()
											{
												view_entity->setPosition( object.position() );
												view_entity->setAngle( object.angle() );
											 });

		mRegisteredListeners[&object] = std::move(update);
	}
}

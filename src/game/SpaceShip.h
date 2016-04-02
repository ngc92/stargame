#ifndef SPACESHIP_H_INCLUDED
#define SPACESHIP_H_INCLUDED

#include "util.h"
#include "GameObject.h"
#include "property/CPropertyObject.h"

namespace game
{
	class ShipStructure;
	class FlightModel;
	class ActionList;

	class SpaceShip : ObjectCounter<SpaceShip>, public GameObject, public property::CPropertyObject
	{
	public:
		SpaceShip(long id, b2Body* body, std::unique_ptr<ShipStructure> structure);
		~SpaceShip();

		const ShipStructure& getStructure() const;

	private:
		void processActions(ActionList& actions);
		void onShipStep();
		void onShipImpact(GameObject* other, const ImpactInfo& info);

		ListenerRef mStepListener;
		ListenerRef mImpactListener;

		std::unique_ptr<ShipStructure> mStructure;
		std::unique_ptr<FlightModel> mFlightModel;
	};
}

#endif // SPACESHIP_H_INCLUDED

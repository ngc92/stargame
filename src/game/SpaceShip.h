#ifndef SPACESHIP_H_INCLUDED
#define SPACESHIP_H_INCLUDED

#include "util.h"
#include "GameObject.h"

namespace game
{
	class ShipStructure;
	class FlightModel;

	class SpaceShip : public ObjectCounter<SpaceShip>, public GameObject
	{
	public:
		SpaceShip();

	private:
		void onShipStep();
		void onShipImpact(GameObject* other, const ImpactInfo& info);

		ListenerRef mStepListener;
		ListenerRef mImpactListener;

		std::unique_ptr<ShipStructure> mStructure;
		std::unique_ptr<FlightModel> mFlightModel;
	};
}

#endif // SPACESHIP_H_INCLUDED

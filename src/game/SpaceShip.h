#ifndef SPACESHIP_H_INCLUDED
#define SPACESHIP_H_INCLUDED

#include "util.h"
#include "GameObject.h"

namespace game
{
	class ShipStructure;
	class FlightModel;
	class ActionList;

	class SpaceShip : public ObjectCounter<SpaceShip>, public GameObject
	{
	public:
		SpaceShip(b2Body* body);
		~SpaceShip();

	private:
		void processActions(ActionList& actions);
		void onShipStep();
		void onShipImpact(GameObject* other, const ImpactInfo& info);

		void iterateProperties( std::function<void(const std::string& object, IPropertyObject*)> fn );

		ListenerRef mStepListener;
		ListenerRef mImpactListener;

		std::unique_ptr<ShipStructure> mStructure;
		std::unique_ptr<FlightModel> mFlightModel;
	};
}

#endif // SPACESHIP_H_INCLUDED

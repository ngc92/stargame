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

		bool step(float dt) override;
		void onImpact(GameObject* other, const ImpactInfo& info) override;

	private:
		std::unique_ptr<ShipStructure> mStructure;
		std::unique_ptr<FlightModel> mFlightModel;
	};
}

#endif // SPACESHIP_H_INCLUDED

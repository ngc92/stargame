#include "SpaceShip.h"
#include "ShipStructure.h"
#include "FlightModel.h"

namespace game
{
	SpaceShip::SpaceShip() : GameObject(),
							mStructure( make_unique<ShipStructure>() ),
							mFlightModel( make_unique<FlightModel>() )
	{

	}

	bool SpaceShip::step(float dt)
	{
		mStructure->update(dt);
		mFlightModel->update_movement( *mBody );
	}
}

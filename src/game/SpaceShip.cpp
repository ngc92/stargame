#include "SpaceShip.h"
#include "ShipStructure.h"
#include "FlightModel.h"
#include "Components/ActionList.h"

namespace game
{
	SpaceShip::SpaceShip() : GameObject(),
							mStructure( make_unique<ShipStructure>() ),
							mFlightModel( make_unique<FlightModel>() )
	{

	}

	bool SpaceShip::step(float dt)
	{
		ActionList lst;
		mStructure->update(dt, lst);

		// now act based on the generated actions
		lst.act( *mFlightModel );
		mStructure->foreachComponent([](IComponent& cmp, ActionList& al){ al.act(cmp); }, std::ref(lst));

		mFlightModel->update_movement( *mBody );
		return true;
	}

	void SpaceShip::onImpact(GameObject* other, const ImpactInfo& info)
	{
		/// \todo sophisticated damage behaviour
		Damage damage(DamageType::BLUNT, info.impulse * 0.0008);
		mStructure->hit(damage, info.position, -info.normal);
	}
}

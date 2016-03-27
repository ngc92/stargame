#include "SpaceShip.h"
#include "ShipStructure.h"
#include "FlightModel.h"
#include "Components/ActionList.h"
#include "Components/IComponent.h"

namespace game
{
	using namespace std::placeholders;
	SpaceShip::SpaceShip(long id, b2Body* body, std::unique_ptr<ShipStructure> structure) :
							GameObject(body, id),
							mStructure( std::move(structure) ),
							mFlightModel( make_unique<FlightModel>() ),
							mStepListener( addStepListener(std::bind(onShipStep, this)) ),
							mImpactListener( addImpactListener(std::bind(onShipImpact, this, _1, _2)) )
	{
		// init
		mStructure->foreachComponent([this](IComponent& c){ this->addPropertyObject(c.name(), &c); });

		ActionList lst;
		mStructure->init(lst, *mInputs);
		processActions(lst);
	}

	SpaceShip::~SpaceShip()
	{

	}

	void SpaceShip::processActions(ActionList& actions)
	{
		// now act based on the generated actions
		actions.act( *mFlightModel );
		mStructure->foreachComponent([](IComponent& cmp, ActionList& al){ al.act(cmp); }, std::ref(actions));
	}

	void SpaceShip::onShipStep()
	{
		ActionList lst;
		mStructure->update(lst);

		processActions(lst);

		mFlightModel->update_movement( *mBody );
	}

	void SpaceShip::onShipImpact(GameObject* other, const ImpactInfo& info)
	{
		/// \todo sophisticated damage behaviour
		Damage damage(DamageType::BLUNT, info.impulse * 0.0008);
		mStructure->hit(damage, info.position, -info.normal);
	}

	const ShipStructure& SpaceShip::getStructure() const
	{
		return *mStructure;
	}
}

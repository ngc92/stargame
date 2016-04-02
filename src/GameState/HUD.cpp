#include "HUD.h"
#include "game/SpaceShip.h"
#include "game/ShipStructure.h"
#include "game/components/IComponent.h"
#include "graphic/SubsystemDamageView.h"
#include <irrlicht/irrlicht.h>
#include <iostream>
#include "property/IPropertyView.h"

HUD::HUD(irr::gui::IGUIEnvironment* env, long ship): mGUIEnv(env), mShipID(ship)
{
	mDmgView = new graphic::SubsystemDamageView(env, env->getRootGUIElement(), 0, irr::core::recti(0,0, 100, 400));
}

void HUD::onSpawn(const game::GameObject& spawned)
{
	if(spawned.getID() != mShipID)
		return;

	// found our ship
	// this can throw!
	auto& ship = dynamic_cast<const game::SpaceShip&>(spawned);
	auto& structure = ship.getStructure();
	const_cast<game::ShipStructure&>(structure).foreachComponent([this](const game::IComponent& comp, graphic::SubsystemDamageView* dmgview)
		{
			auto view = dmgview->addSubSystem(comp.name());

			auto lst = comp.getProperty("HP").addListener([view, &comp](property::IPropertyView& p)
			{
				/// \todo this breaks thread safety! fix!
				view->status = comp.HP() / comp.maxHP();
			});
/*
			auto lst = comp.addInsertListener("HP", );
*/
			view->status = comp.HP() / comp.maxHP();

			mListeners.push_back(std::move(lst));
		}, mDmgView
	);
}

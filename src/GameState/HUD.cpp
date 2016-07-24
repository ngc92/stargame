#include "HUD.h"
#include "game/IGameObjectView.h"
#include "game/IGameWorldView.h"
#include "graphic/SubsystemDamageView.h"
#include "graphic/CShipStatusView.h"
#include "graphic/ShipStatusCtrl.h"
#include "graphic/tactical_map/CTacticalMapView.h"
#include "graphic/tactical_map/TacticalMapCtrl.h"
#include <irrlicht/irrlicht.h>
#include <iostream>
#include "property/IPropertyView.h"

HUD::HUD(irr::gui::IGUIEnvironment* env, long ship): mShipID(ship), mGUIEnv(env)
{
	mDmgView = new graphic::SubsystemDamageView(env, env->getRootGUIElement(), 0, irr::core::recti(0,0, 100, 200));
	mStaView = new graphic::CShipStatusView(env, env->getRootGUIElement(), 0, irr::core::recti(690, 10, 790, 110));
	mTacMap = new graphic::detail::CTacticalMapView(env, env->getRootGUIElement(), 0, irr::core::recti(10, 490, 110, 590));
}
HUD::~HUD()
{

}

void HUD::init( game::IGameWorldView& world_view )
{
	using std::placeholders::_1;
	mListeners.push_back(world_view.addSpawnListener(std::bind(&HUD::onSpawn, this, _1)));
	mTacCtrl = std::make_unique<graphic::TacticalMapCtrl>(mTacMap, world_view);
}

void HUD::onSpawn(const game::IGameObjectView& spawned)
{
	if(spawned.id() != mShipID)
		return;

	// found our ship.
	mStatCtrl = std::make_unique<graphic::ShipStatusControl>(mStaView, spawned);
	spawned.getChild("structure").forallChildren([this](const property::IPropertyObjectView& view){ processChild(view); });
}

void HUD::processChild(const property::IPropertyObjectView& child)
{
	using boost::get;

	if(child.name().substr(0, 6) != "armour")
	{
		auto view = mDmgView->addSubSystem(child.name());

		auto updateHP = [view](property::IPropertyView& p)
		{
			view->status = get<float>(p.owner()->getProperty("HP").value()) / get<float>(p.owner()->getProperty("maxHP").value());
		};

		mListeners.push_back(child.getProperty("HP").addListener(updateHP));
		mListeners.push_back(child.getProperty("maxHP").addListener(updateHP));

		updateHP( child.getProperty("HP") );
	}
}

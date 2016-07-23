#include "FixedGun.h"
#include <iostream>

#include "consts.h"
#include "game/IGameObject.h"
#include "game/spawn/SpawnData.h"
#include "game/WorldAction.h"
#include "game/ai/IAIRegistrator.h"

namespace game
{
namespace components
{
	FixedGun::FixedGun():
		CComponent(100, 100, "FixedGun"),
		mAmmoType("ammo_type", this, std::string("AP")),
		mAmmoAmount("ammo_amount", this, 1000),
		mPrecision("precision", this, 1),
		mCaliber("caliber", this, 10),
		mRPM("rpm", this, 60),
		mReloadTimer("reload_timer", this, 0.f),
		mFireButton("input:fire", this, 0.f)
	{
	}

	void FixedGun::init(IGameObject& object)
	{
	}

	void FixedGun::registerAtAI( ai::IAIRegistrator& reg )
	{
		mAiReg = reg.registerWeaponSystem(*this);
	}

	void FixedGun::step(IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action)
	{
		mReloadTimer -= STEP_TIME;

		if(!mFireButton.value())
			return;

		if( mReloadTimer < 0 && mAmmoAmount > 0)
		{
			mReloadTimer = 60 / mRPM;
			mAmmoAmount -= 1;
			spawn::SpawnData data(ObjectCategory::BULLET, mAmmoType.value(), b2Vec2(0,0));
			data.origin = &object;
			subordinate(data, object);
			push_action( spawn::make_spawner(data) );
		}
	}

	void FixedGun::fire()
	{
		mFireButton = 1.f;
	}

	REG_COMP_MACRO(FixedGun);
}
}

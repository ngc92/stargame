#include "FixedGun.h"
#include <iostream>

#include "consts.h"
#include "game/SpawnManager.h"
#include "game/IGameObject.h"
#include <Box2D/Dynamics/b2Body.h>

namespace game
{
namespace components
{
	FixedGun::FixedGun():
		CComponent(100, 100, "FixedGun"),
		mAmmoType("ammo_type", this, std::string("AP")),
		mAmmoAmount("ammo_amount", this, 100),
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

	void FixedGun::step(IGameObject& object, IGameWorld& world)
	{
		mReloadTimer -= STEP_TIME;

		if(!mFireButton.value())
			return;

		if( mReloadTimer < 0 && mAmmoAmount > 0)
		{
			mReloadTimer = 60 / mRPM;
			mAmmoAmount -= 1;
			SpawnInitData data(world, mAmmoType.value());
			SpawnManager::singleton().createBullet(data, object);
		}
	}
}
}

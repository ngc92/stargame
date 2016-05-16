#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "CComponent.h"

namespace game
{
namespace components
{
	class FixedGun : public CComponent
	{

	public:
		FixedGun();
		void init(IGameObject& object) override;
		void step(IGameObject& object, IGameWorld& world) override;

	private:
		Property<std::string> mAmmoType;
		Property<int> mAmmoAmount;
		Property<float> mPrecision;
		Property<float> mCaliber;
		Property<float> mRPM;

		// status
		Property<float> mReloadTimer;

		// control
		Property<float> mFireButton; /// \todo enable bool controls!
	};
}
}

#endif // WEAPON_H_INCLUDED

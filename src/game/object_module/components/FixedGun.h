#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "CComponent.h"
#include "game/ai/IWeaponSystem.h"

namespace game
{
namespace components
{
	class FixedGun : public CComponent, public ai::IWeaponSystem
	{

	public:
		FixedGun();
		void init(IGameObject& object) override;
		void step(IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action) override;

		// IWeaponSystem interface
		void registerAtAI( ai::IAIRegistrator& reg ) override;

		// action functions
		void fire() override;
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

		std::shared_ptr<void> mAiReg;; //!< this variable contains just a d'tor to unregister

	};
}
}

#endif // WEAPON_H_INCLUDED

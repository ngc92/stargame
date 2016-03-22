#include "ArmourSegment.h"
#include "Damage.h"

namespace game
{
	ArmourSegment::ArmourSegment(float hp) :
		mHP(hp), mMaxHP(hp)
	{

	}

	ArmourSegment::ArmourSegment(float hp, Damage absorb, Damage transmit, Damage destruct):
		mHP(hp), mMaxHP(hp), mAbsorbtion(absorb), mTransmission(transmit), mDestruction(destruct)
	{

	}

	float ArmourSegment::hp() const
	{
		return mHP;
	}

	float ArmourSegment::max_hp() const
	{
		return mMaxHP;
	}

	float ArmourSegment::hp_status() const
	{
		return mHP/mMaxHP;
	}

	Damage ArmourSegment::hit(Damage damage)
	{
		damage.absorb(mAbsorbtion * hp_status());

        Damage armour_dmg = damage * mDestruction;
        Damage transmit_dmg = damage * mTransmission;

        float maxDmg = armour_dmg.getTotalDamage();
        float realDmg = std::min(mHP, maxDmg);
		mHP = std::max(0.f, mHP - maxDmg);

        return transmit_dmg + transmit_dmg*(1 - realDmg/maxDmg);
	}
}

#include "ArmourSegment.h"
#include "property/CPropertyObject.h"

namespace game
{
	ArmourSegment::ArmourSegment(float hp) :
		mProperties( std::make_shared<property::CPropertyObject>("armour")),
		mHP("HP", mProperties.get(), hp), mMaxHP("maxHP", mProperties.get(), hp)
	{

	}

	ArmourSegment::ArmourSegment(float hp, Damage absorb, Damage transmit, Damage destruct):
		mProperties( std::make_shared<property::CPropertyObject>("armour")),
		mHP("HP", mProperties.get(), hp), mMaxHP("maxHP", mProperties.get(), hp), mAbsorbtion(absorb), mTransmission(transmit), mDestruction(destruct)
	{

	}
	
	ArmourSegment::~ArmourSegment()
	{
		if(mProperties)
		{
			auto par = dynamic_cast<const property::IPropertyObject*>(mProperties->parent());
			if(par)
				const_cast<property::IPropertyObject*>(par)->removeChild(*mProperties);
		}
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
		float realDmg = std::min((float)mHP, maxDmg);
		float newHP = std::max(0.f, mHP - maxDmg);
		mHP = newHP;

		return transmit_dmg + transmit_dmg*(1 - realDmg/maxDmg);
	}

	const std::shared_ptr<property::IPropertyObject>& ArmourSegment::getSharedPropertyObject()
	{
		return mProperties;
	}
}

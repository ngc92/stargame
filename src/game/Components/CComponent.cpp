#include "CComponent.h"
#include <cassert>
#include <irrlicht/IAttributes.h>

namespace game
{
namespace components
{
	CComponent::CComponent(/*const*/ irr::io::IAttributes& a):
				mWeight( "weight", a.getAttributeAsFloat("weight") ),
				mMaxHP( "maxHP", a.getAttributeAsFloat("HP")),
				mType( "type", a.getAttributeAsString("damage_factor").c_str()),
				mHP( "HP", mMaxHP )
	{
	}

	float CComponent::weight() const
	{
		return mWeight;
	}

	float CComponent::maxHP() const
	{
		return mMaxHP;
	}

	float CComponent::HP() const
	{
		return mHP;
	}

	const std::string& CComponent::type() const
	{
		return mType;
	}

	bool CComponent::canSupply(const std::string& resource) const
	{
		return false;
	}

	float CComponent::getSupply(const std::string& resource, float amount)
	{
		assert(0);
	}

	void CComponent::registerSupplier(const std::string& resource, IComponent* component)
	{
		assert(0);
	}

	float CComponent::onDamage( float dam )
	{
		if(dam > mHP)
		{
			return damage(mHP);
		}
		mHP = mHP - dam;
		return dam;
	}


	DamageListenerList& CComponent::getDamageListeners()
	{
		return mDamageListeners;
	}
}
}


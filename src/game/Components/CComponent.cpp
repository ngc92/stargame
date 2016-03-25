#include "CComponent.h"
#include <cassert>

namespace game
{
namespace components
{
	CComponent::CComponent(float weight, float hp, const std::string& name):
				mWeight( "weight", weight ),
				mMaxHP( "maxHP", hp ),
				mName( "name", name ),
				mHP( "HP", hp )
	{
		properties().addProperty(mWeight)
					.addProperty(mMaxHP)
					.addProperty(mName)
					.addProperty(mHP);
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

	const std::string& CComponent::name() const
	{
		return mName;
	}

	const IPropertyCollection& CComponent::properties() const
	{
		return mProperties;
	}

	CPropertyCollection& CComponent::properties()
	{
		return mProperties;
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


#include "CComponent.h"
#include <cassert>

namespace game
{
namespace components
{
	CComponent::CComponent(float weight, float hp, const std::string& name):
				CPropertyObject(std::move(name)),
				mWeight( "weight", this, weight ),
				mMaxHP( "maxHP", this, hp ),
				mHP( "HP", this, hp )
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
		mHP -= dam;
		return dam;
	}


	DamageListenerList& CComponent::getDamageListeners()
	{
		return mDamageListeners;
	}
}
}


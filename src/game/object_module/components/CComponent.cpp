#include "CComponent.h"
#include "game/IGameObject.h"
#include "game/object_module/ISubStructure.h"
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
	
	void CComponent::setWeight( float weight )
	{
		mWeight = weight;
	}
	
	void CComponent::setHitPoints( float current, float max )
	{
		mHP = current;
		if(max > 0)
			mMaxHP = max;
	}

	bool CComponent::canSupply(const std::string& resource) const
	{
		return false;
	}

	float CComponent::getSupply(const std::string& resource, float amount)
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


	std::weak_ptr<IComponent> getSupplier( IGameObject& object, const std::string& resource )
	{
        // first, check for the ISubStructure module
        auto sstr = object.getModuleAsType<ISubStructure>();
		for(auto& cell : sstr->getCells())
		{
			// we cannot use simple range iteration, because we want to access
			// the shared_ptr
			std::size_t count = cell.component_count();
			for(std::size_t i = 0; i < count; ++i)
			{
                auto comp = cell.getComponent(i);
                if(comp->canSupply(resource))
				{
					return comp;
				}
			}
		}

		return std::weak_ptr<IComponent>();

	}
}
}


#include "IComponent.h"
#include <irrlicht/IAttributes.h>

namespace game
{
	IComponent::IComponent(/*const*/ irr::io::IAttributes& a):
				mWeight( "weight", a.getAttributeAsFloat("weight") ),
				mMaxHP( "maxHP", a.getAttributeAsFloat("HP")),
				mMaxRepairHP( a.getAttributeAsFloat("repairHP")),
				mType( "type", a.getAttributeAsString("damage_factor").c_str()),
				mHP( "HP", mMaxHP )
	{
	}

	float IComponent::weight() const
	{
		return mWeight;
	}

	float IComponent::maxHP() const
	{
		return mMaxHP;
	}

	float IComponent::HP() const
	{
		return mHP;
	}

	const std::string& IComponent::type() const
	{
		return mType;
	}

	float IComponent::damage( float dam )
	{
		// small damage can always be repaired 2 + 0.5%
		float rep_dmg = 2 + 0.005 * mMaxHP;

		if(dam > mHP)
		{
			return damage(mHP);
		}
		fireDmgChangeEvent(dam);
		mHP = mHP - dam;
		mMaxRepairHP -= std::max(0.0, dam * 0.5 - rep_dmg);
		return dam;
	}

	IComponent::dmgListenerPtr IComponent::addDmgListener(dmgListener l)
	{
		mDmgListenerList.push_back(l);
		return --mDmgListenerList.end();
	}

	void IComponent::removeDmgListener(dmgListenerPtr l_ptr)
	{
		mDmgListenerList.erase(l_ptr);
	}

	void IComponent::fireDmgChangeEvent(float dmg)
	{
		std::list<dmgListener> workList = mDmgListenerList;
		for(auto& lst : workList)
		{
			lst(dmg);
		}
	}

	void IComponent::repair( float time_sec )
	{
		mHP = std::min( mMaxRepairHP, mHP + time_sec );
	}
}


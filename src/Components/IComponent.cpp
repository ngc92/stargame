#include "IComponent.h"
#include <irrlicht/IAttributes.h>

IComponent::IComponent(/*const*/ irr::io::IAttributes& a, SpaceShip* ship):
			mShip(ship),
			mWeight(a.getAttributeAsFloat("weight") ),
			mMaxHP( a.getAttributeAsFloat("HP")),
			mMaxRepairHP( a.getAttributeAsFloat("repairHP")),
			mType( a.getAttributeAsString("damage_factor").c_str())
{
}

float IComponent::getWeight()
{
	return mWeight;
}
int IComponent::getMaxHP()
{
	return mMaxHP;
}
int IComponent::getCurrHP()
{
	return mCurrHP;
}
std::string IComponent::getType()
{
	return mType;
}

float IComponent::damage( float dam )
{
				// small damage can always be repaired 2 + 0.5%
			float rep_dmg = 2 + 0.005 * mMaxHP;

			if(dam > mCurrHP)
			{
				return damage(mCurrHP);
			}
			fireDmgChangeEvent(dam);
			mCurrHP -= dam;
			mMaxRepairHP -= std::max(0.0, dam * 0.5 - rep_dmg);
			return dam;
}

IComponent::dmgListenerPtr IComponent::addDmgListener(dmgListener l)
{
	dmgListenerList.push_back(l);
	return --dmgListenerList.end();
}

void IComponent::removeDmgListener(dmgListenerPtr l_ptr)
{
	dmgListenerList.erase(l_ptr);
}

void IComponent::fireDmgChangeEvent(float dmg)
{
	std::list<dmgListener> workList = dmgListenerList;
    for(auto& lst : workList)
	{
		lst(dmg);
    }
}

void IComponent::repair( float time_sec )
{
	mCurrHP = std::min( mMaxRepairHP, mCurrHP + time_sec );
}



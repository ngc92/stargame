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
<<<<<<< HEAD
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
=======
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
>>>>>>> refs/remotes/origin/master
}

IComponent::dmgListenerPtr IComponent::addDmgListener(dmgListener l)
{
<<<<<<< HEAD
	dmgListenerList.push_back(l);
	return --dmgListenerList.end();
=======
	mDmgListenerList.push_back(l);
	return --mDmgListenerList.end();
>>>>>>> refs/remotes/origin/master
}

void IComponent::removeDmgListener(dmgListenerPtr l_ptr)
{
<<<<<<< HEAD
	dmgListenerList.erase(l_ptr);
=======
	mDmgListenerList.erase(l_ptr);
>>>>>>> refs/remotes/origin/master
}

void IComponent::fireDmgChangeEvent(float dmg)
{
<<<<<<< HEAD
	std::list<dmgListener> workList = dmgListenerList;
=======
	std::list<dmgListener> workList = mDmgListenerList;
>>>>>>> refs/remotes/origin/master
    for(auto& lst : workList)
	{
		lst(dmg);
    }
}

void IComponent::repair( float time_sec )
{
	mCurrHP = std::min( mMaxRepairHP, mCurrHP + time_sec );
}



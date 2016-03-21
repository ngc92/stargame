#include "ShipComponent.h"
#include <irrlicht/IAttributes.h>

ShipComponent::ShipComponent(/*const*/ irr::io::IAttributes& a, Spaceship* ship):
			mShip(ship),
			mWeight(a.getAttributeAsFloat("weight") ),
			mMaxHP( a.getAttributeAsFloat("HP")),
			mMaxRepairHP( a.getAttributeAsFloat("repairHP")),
			mType( a.getAttributeAsString("damage_factor").c_str())
{
}

float ShipComponent::getWeight()
{
	return mWeight;
}
int ShipComponent::getMaxHP()
{
	return mMaxHP;
}
int ShipComponent::getCurrHP()
{
	return mCurrHP;
}
std::string ShipComponent::getType()
{
	return mType;
}

float ShipComponent::damage( float dam )
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


void ShipComponent::fireDmgChangeEvent(float dmg)
{
    for(auto& lst : dmgListenerList)
	{
		lst(dmg);
    }
}

void ShipComponent::repair( float time_sec )
{
	mCurrHP = std::min( mMaxRepairHP, mCurrHP + time_sec );
}



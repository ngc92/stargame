#include "IGun.h"

IGun::IGun(/*const*/ irr::io::IAttributes& a, SpaceShip* ship):
	IWeapon(a,ship),
	mMaxAmmo(a.getAttributeAsFloat("MaxAmmo")),
	mCurrAmmo(1)
{
}

float IGun::getMaxAmmo()
{
	return mMaxAmmo;
}

float IGun::getCurrAmmo()
{
	return mCurrAmmo;
}

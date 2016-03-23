#ifndef IGUN_H_INCLUDED
#define IGUN_H_INCLUDED

#include "IWeapon.h"

class IGun : IWeapon
{
public:
	IGun(/*const*/ irr::io::IAttributes& a, SpaceShip* ship);

	float getMaxAmmo();
	float getCurrAmmo();

private:
	float mCurrAmmo;
	float mMaxAmmo;




};

#endif // IGUN_H_INCLUDED

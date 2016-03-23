#ifndef GUNMACHINE_H_INCLUDED
#define GUNMACHINE_H_INCLUDED

#include "IGun.h"

class GunMachine : IGun
{
public:
	GunMachine(/*const*/ irr::io::IAttributes& a, SpaceShip* ship);

};

#endif // GUNMACHINE_H_INCLUDED

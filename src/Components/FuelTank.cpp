#include "FuelTank.h"
#include <cstdlib>
#include <iostream>

FuelTank::FuelTank(irr::io::IAttributes& a, SpaceShip* myship) : IComponent( a, myship )
{

}

FuelTank::~FuelTank()
{
}

void FuelTank::step(float time_sec, IActionListInterface& actionlist)
{
}

bool FuelTank::canSupply(const std::string& resource) const
{
	return mFuel > 0 && resource == "fuel";
}

float FuelTank::getSupply(const std::string& resource, float amount)
{
	assert( resource == "fuel" );
	if(mFuel > amount)
	{
		mFuel -= amount;
		return amount;
	}
	else
	{
		amount = mFuel;
		mFuel = 0;
		return amount;
	}
}
void FuelTank::registerSupplier(const std::string& resource, IComponent* component)
{
	assert(0);
}

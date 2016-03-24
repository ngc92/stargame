#include "FuelTank.h"
#include <cstdlib>
#include <iostream>

namespace game
{
	FuelTank::FuelTank(irr::io::IAttributes& a) : IComponent( a )
	{

	}

	FuelTank::~FuelTank()
	{
	}

	void FuelTank::step(IActionListInterface& actionlist)
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
}

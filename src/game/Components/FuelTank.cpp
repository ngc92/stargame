#include "FuelTank.h"
#include <cstdlib>
#include <iostream>

namespace game
{
namespace components
{
	FuelTank::FuelTank(): CComponent(50, 100, "FuelTank"),
		mCapacity("capacity", this, 100),
		mMaxPump("maxpump", this, 1),
		mFuel("fuel", this, 100)
	{
	}

	FuelTank::~FuelTank()
	{
	}

	void FuelTank::init(IActionListInterface& actionlist, input::IInputCollection& inputs)
	{
	}

	void FuelTank::step(IActionListInterface& actionlist)
	{
		mPumpLeft = mMaxPump;
	}

	bool FuelTank::canSupply(const std::string& resource) const
	{
		return mFuel > 0 && resource == "fuel";
	}

	float FuelTank::getSupply(const std::string& resource, float amount)
	{
		assert( resource == "fuel" );
		float max_supply = std::min((float)mFuel, mPumpLeft);
		if(max_supply < amount )
			amount = max_supply;

		mFuel -= amount;
		mPumpLeft -= amount;
		return amount;
	}
}
}

#include "FuelTank.h"
#include <cstdlib>
#include <iostream>

namespace game
{
namespace components
{
	FuelTank::FuelTank(): CComponent(50, 100, "FuelTank"),
		mCapacity("capacity", this, 1000),
		mMaxPump("maxpump", this, 1),
		mFuel("fuel", this, 10000)
	{
	}

	FuelTank::~FuelTank()
	{
	}

	void FuelTank::init(IGameObject& object)
	{
		mFuel = std::max((float)mCapacity, (float)mFuel);
	}

	void FuelTank::step()
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

#include "FuelTank.h"
#include <cstdlib>
#include <iostream>

namespace game
{
	FuelTank::FuelTank(irr::io::IAttributes& a) : IComponent( a ),
		mCapacity("capacity", 100),
		mMaxPump("maxpump", 1),
		mFuel("fuel", 100)
	{

	}

	FuelTank::~FuelTank()
	{
	}

	void FuelTank::init(IActionListInterface& actionlist)
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
		float max_supply = std::min(mFuel.value(), mPumpLeft);
		if(max_supply < amount )
			amount = max_supply;

		mFuel -= amount;
		mPumpLeft -= amount;
		return amount;
	}

	void FuelTank::registerSupplier(const std::string& resource, IComponent* component)
	{
		assert(0);
	}
}

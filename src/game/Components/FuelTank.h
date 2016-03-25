#ifndef FUELTANK_H_INCLUDED
#define FUELTANK_H_INCLUDED

#include "CComponent.h"
#include "util/Property.h"

namespace game
{
namespace components
{
	/*!
		\todo add the following features to FuelTanks:
				* damage effect: fuel leak
				* property: max pump rate
				* set components weight according to amount of
					fuel
	*/
	class FuelTank : public CComponent
	{
		public:
			FuelTank();
			virtual ~FuelTank();

			void init(IActionListInterface& actionlist) override;
			void step(IActionListInterface& actionlist) override;

			bool canSupply(const std::string& resource) const override;
			float getSupply(const std::string& resource, float amount) override;
		private:
			// fuel tank parameters
			Property<float> mCapacity;
			Property<float> mMaxPump;

			// fuel tank status
			Property<float> mFuel;

			// processing variables
			float mPumpLeft;
	};
}
}
#endif // FUELTANK_H_INCLUDED

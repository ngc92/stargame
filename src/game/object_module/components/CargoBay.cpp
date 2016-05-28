#include "CargoBay.h"
#include <cstdlib>
#include <iostream>
namespace game
{

	namespace components
	{
		CargoBay::CargoBay() : CComponent(100, 100, "CargoBay"),
		mCapacity( "capacity", this, 100.f ),
		mCargo(std::make_shared<property::CPropertyObject>("cargo"))
		{

		}

		CargoBay::~CargoBay()
		{
		}

		void CargoBay::init(IGameObject& object)
		{

		}

		void CargoBay::step(IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action)
		{

		}

		bool CargoBay::canSupply(const std::string& resource) const
		{
			return mCargo->hasProperty(resource);
		}

		float CargoBay::getSupply(const std::string& resource, float amount)
		{
			auto& prop = mCargo->getProperty(resource);
			/// \todo what do we do in case we have an int here?
			/// would make sense for ammo etc.
			auto present = boost::get<float>(prop.value());

			float mx = std::max(present, amount);
			present -= mx;
			dynamic_cast<property::IProperty&>(prop).changable_value() = present;
			return mx;
		}
	}
}

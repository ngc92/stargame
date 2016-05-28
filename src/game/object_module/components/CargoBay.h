#ifndef CARGOBAY_H_INCLUDED
#define CARGOBAY_H_INCLUDED

#include "CComponent.h"

namespace game
{
	namespace components
	{
		class CargoBay : public CComponent
		{
			public:
				CargoBay();
				virtual ~CargoBay();

				void init(IGameObject& object) final;
				void step(IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action) final;

				bool canSupply(const std::string& resource) const final;
				float getSupply(const std::string& resource, float amount) final;

			private:
				Property<float> mCapacity;

				// Carried things
				std::shared_ptr<property::IPropertyObject> mCargo;

		};
	}
}

#endif // CARGOBAY_H_INCLUDED

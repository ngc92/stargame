#ifndef CCOMPONENT_H_INCLUDED
#define CCOMPONENT_H_INCLUDED

#include "IComponent.h"
#include "util/Property.h"

namespace game
{
class SpaceShip;
class IActionListInterface;
namespace components
{
	class CComponent : public IComponent
	{
		public:
			CComponent(irr::io::IAttributes& a);
			virtual ~CComponent() = default;

			float onDamage( float dam ) final;

			// common properties
			float weight() 				const final;
			float maxHP() 				const final;
			float HP() 					const final;
			const std::string& type() 	const final;

			// supply interface
			bool canSupply(const std::string& resource) const override;
			float getSupply(const std::string& resource, float amount) override;
			void registerSupplier(const std::string& resource, IComponent* component) override;
		private:
			DamageListenerList& getDamageListeners() final;

			Property<float> mWeight;
			Property<float> mMaxHP;
			Property<std::string> mType;
			Property<float> mHP;

			DamageListenerList mDamageListeners;
	};
}
}

#endif // CCOMPONENT_H_INCLUDED

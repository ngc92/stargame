#ifndef CCOMPONENT_H_INCLUDED
#define CCOMPONENT_H_INCLUDED

#include "IComponent.h"
#include "util/Property.h"
#include "util/CPropertyCollection.h"

namespace game
{
class SpaceShip;
class IActionListInterface;
namespace components
{
	class CComponent : public IComponent
	{
		public:
			CComponent(float weight, float hp, const std::string& name);
			virtual ~CComponent() = default;

			float onDamage( float dam ) final;

			// common properties
			float weight() 				const final;
			float maxHP() 				const final;
			float HP() 					const final;
			const std::string& name() 	const final;
			const IPropertyCollection& properties() const final;

			// supply interface
			bool canSupply(const std::string& resource) const override;
			float getSupply(const std::string& resource, float amount) override;
			void registerSupplier(const std::string& resource, IComponent* component) override;
		protected:
			CPropertyCollection& properties();
		private:
			DamageListenerList& getDamageListeners() final;

			Property<float> mWeight;
			Property<float> mMaxHP;
			Property<std::string> mName;
			Property<float> mHP;

			CPropertyCollection mProperties;

			DamageListenerList mDamageListeners;
	};
}
}

#endif // CCOMPONENT_H_INCLUDED

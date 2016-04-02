#ifndef CCOMPONENT_H_INCLUDED
#define CCOMPONENT_H_INCLUDED

#include "IComponent.h"
#include "property/CPropertyObject.h"
#include "property/TypedProperty.h"


namespace game
{
class SpaceShip;
class IActionListInterface;
namespace components
{
	template<class T>
	using Property = property::TypedProperty<T>;

	class CComponent : public IComponent, public property::CPropertyObject
	{
		public:
			CComponent(float weight, float hp, const std::string& name);
			virtual ~CComponent() = default;

			float onDamage( float dam ) final;

			// common properties
			float weight() 				const final;
			float maxHP() 				const final;
			float HP() 					const final;

			// supply interface
			bool canSupply(const std::string& resource) const override;
			float getSupply(const std::string& resource, float amount) override;
			void registerSupplier(const std::string& resource, IComponent* component) override;
		protected:
		//private:
			DamageListenerList& getDamageListeners() final;

			Property<float> mWeight;
			Property<float> mMaxHP;
			Property<float> mHP;

			DamageListenerList mDamageListeners;
	};
}
}

#endif // CCOMPONENT_H_INCLUDED

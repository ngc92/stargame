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
			float weight() 	const final;
			float maxHP() 	const final;
			float HP() 		const final;
			
			void setWeight( float weight ) final;
			void setHitPoints( float current, float max = -1 ) final;

			// supply interface
			bool canSupply(const std::string& resource) const override;
			float getSupply(const std::string& resource, float amount) override;
		protected:
		//private:
			DamageListenerList& getDamageListeners() final;

			Property<float> mWeight;
			Property<float> mMaxHP;
			Property<float> mHP;

			DamageListenerList mDamageListeners;
	};


	// utility functions
	/// tries to find a supplier for \p resource within the components of \p object.
	/// This requires \p object to have a ISubStructure module.
	std::weak_ptr<IComponent> getSupplier( IGameObject& object, const std::string& resource );
	
	
	// helper to register a component type
	template<class T>
	struct RegisterComponentCreation
	{
		RegisterComponentCreation(std::string name)
		{
			registerComponentConstructor<T>( std::move(name) );
		}
	};
	
	/// use this macro to register a component for creation
	#define REG_COMP_MACRO(T) 	\
	namespace {	auto T##_registrator = RegisterComponentCreation<T>(#T); }
}
}

#endif // CCOMPONENT_H_INCLUDED

#ifndef SHIPCOMPONENT_H_INCLUDED
#define SHIPCOMPONENT_H_INCLUDED

#include <string>
#include "util.h"
#include "util/ListenerList.h"
#include "util/IPropertyCollection.h"

namespace game
{
	class SpaceShip;
	class IActionListInterface;

	/*! \namespace components
		\brief namespace for all ship components.
		\details This namespace contains the implementations
				for the different kind of ship components.
				It is supposed to be a completely modular unit, i.e.
				there should never be any need to access internals of
				this namespace from the outside.
				The only exported class is the IComponent interface.
	*/
	namespace components
	{
		/// \todo add a DamageEvent here
		typedef ListenerList<float> DamageListenerList;

		/*! \class IComponent
			\brief Base class for all ship components.
			\details This class defines the interface for ship components,
					and is the only way how components can communicate
					with the outside world. A default implementation of
					common methods is provided in CComponent, so it is
					recommended that new component classes be derived from
					that.
		*/
		class IComponent : ObjectCounter<IComponent>, public IPropertyObject
		{
			public:
				IComponent() = default;
				virtual ~IComponent() = default;

				virtual void init(IActionListInterface& actionlist) = 0;
				virtual void step(IActionListInterface& actionlist) = 0;
				virtual float onDamage(float dam) = 0;

				// ----------------------------------------------------------------------
				//					non virtual functions that relay work
				// ----------------------------------------------------------------------
				float damage(float dam);

				// ----------------------------------------------------------------------
				//							listeners
				// ----------------------------------------------------------------------
				template<class T>
				ListenerRef addDamageListener(T&& l);

				// ----------------------------------------------------------------------
				//			default properties every component should implement
				// ----------------------------------------------------------------------
				virtual float weight() 	const = 0;
				virtual float maxHP() 	const = 0;
				virtual float HP() 		const = 0;
				virtual const std::string& name() const = 0;
				virtual const IPropertyCollection& properties() const = 0;

				// ----------------------------------------------------------------------
				// 					component connection interface
				// ----------------------------------------------------------------------
				/// this functions returns whether this component offers
				/// resource as a supply.
				virtual bool canSupply(const std::string& resource) const = 0;

				/// this function is called by other components to get resource
				/// from this component.
				/// \return how much was actually supplied.
				virtual float getSupply(const std::string& resource, float amount) = 0;

				/// this function is called to register another component as a supplier
				/// for a certain resource.
				virtual void registerSupplier(const std::string& resource, IComponent* component) = 0;

			private:
				/// gives a reference to the damage listener list.
                virtual DamageListenerList& getDamageListeners() = 0;
		};

		template<class T>
		ListenerRef IComponent::addDamageListener(T&& l)
		{
			return getDamageListeners().addListener(l);
		}

		inline float IComponent::damage(float dam)
		{
			float actual = onDamage(dam);
			getDamageListeners().notify(actual);
			return actual;
		}
	}

	using components::IComponent;
}

#endif // SHIPCOMPONENT_H_INCLUDED

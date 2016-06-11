#ifndef SHIPCOMPONENT_H_INCLUDED
#define SHIPCOMPONENT_H_INCLUDED

#include <string>
#include <functional>
#include "util.h"
#include "listener/listenerlist.h"
#include "property/IPropertyObject.h"

namespace game
{
	class IGameObject;
	class IGameWorld;
	class WorldActionQueue;

	/*! \brief namespace for all ship components.
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
		class IComponent : ObjectCounter<IComponent>, public virtual property::IPropertyObject
		{
			public:
				IComponent() = default;
				virtual ~IComponent() = default;

				virtual void init(IGameObject& object) = 0;
				virtual void step(IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action) = 0;
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

				// setters
				virtual void setWeight( float weight ) = 0;
				virtual void setHitPoints( float current, float max = -1 ) = 0;

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

			private:
				/// gives a reference to the damage listener list.
				virtual DamageListenerList& getDamageListeners() = 0;
		};

		template<class T>
		ListenerRef IComponent::addDamageListener(T&& l)
		{
			return getDamageListeners().addListener(l);
		}
	}

	using components::IComponent;

	// ----------------------------------------------------------------------------------------
	// 		use this to register component types to the component factory
	// ----------------------------------------------------------------------------------------
	namespace components
	{
		namespace detail
		{
			void registerComponentConstructor( std::string name, std::function<std::shared_ptr<IComponent>()> ctor_fn );
		}

		template<class T>
		void registerComponentConstructor(std::string name)
		{
			detail::registerComponentConstructor( move(name), [](){ return std::make_shared<T>(); } );
		}

		std::shared_ptr<IComponent> construct(const std::string& type);
	}
}

#endif // SHIPCOMPONENT_H_INCLUDED

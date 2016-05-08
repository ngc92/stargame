#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "IComponent.h"

namespace game
{
	enum AmmunitionType
	{
		ROCKET,
		PLASMA,
		LASER,
		BULLET
	};

	class IWeapon : IComponent
	{

	public:

		virtual void init(IActionListInterface& actionlist, input::IInputCollection& inputs) = 0;
		virtual void step(IActionListInterface& actionlist) = 0;
		virtual float onDamage(float dam) = 0;

		// ----------------------------------------------------------------------
		//			default properties every component should implement
		// ----------------------------------------------------------------------
		virtual float weight() 	const = 0;
		virtual float maxHP() 	const = 0;
		virtual float HP() 		const = 0;

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
		
		float loadingProgress;
		bool mIsBusy;
		float maxAmmoCount;
		float currAmmoCount;
		std::list<stateListener> stateListenerList;
	};
}

#endif // WEAPON_H_INCLUDED

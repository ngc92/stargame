#ifndef SHIPCOMPONENT_H_INCLUDED
#define SHIPCOMPONENT_H_INCLUDED

#include <string>
#include <list>
#include <functional>
#include <irrlicht/IAttributes.h>
#include "util.h"

namespace game
{
	class SpaceShip;
	class IActionListInterface;

	class IComponent : ObjectCounter<IComponent>
	{
		public:
			using dmgListener = std::function<void(float)>;
			using dmgListenerPtr = std::list<dmgListener>::iterator;

			IComponent(irr::io::IAttributes& a, SpaceShip* myship );
			virtual ~IComponent() = default;

			// non-virtual functions
			float damage( float dam );
			void repair( float time_sec );
			dmgListenerPtr addDmgListener(dmgListener l);
			void removeDmgListener(dmgListenerPtr l_ptr);

			float getWeight();
			int getMaxHP();
			int getCurrHP();
			std::string getType();

			// virtual functions
			virtual float getStatus(std::string bez) = 0;
			virtual void step(float time_sec, IActionListInterface& actionlist) = 0;
			virtual void onDamage(float dam) = 0;
			virtual int actionPerformed(int ctrlbits, float dt) = 0;

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
			float mWeight;
			float mMaxHP;
			std::string mType;
			float mMaxRepairHP;
			SpaceShip* mShip;
			std::list<dmgListener> mDmgListenerList;
			float mCurrHP;

			void fireDmgChangeEvent(float dmg);

	};

}

#endif // SHIPCOMPONENT_H_INCLUDED

#ifndef SHIPCOMPONENT_H_INCLUDED
#define SHIPCOMPONENT_H_INCLUDED

#include <string>
#include <list>
#include <functional>
#include <irrlicht/IAttributes.h>
#include "util.h"

class SpaceShip;

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

		virtual float getStatus(std::string bez) = 0;
		virtual void step(float time_sec) = 0;
		virtual void onDamage(float dam) = 0;
		virtual int actionPerformed(int ctrlbits, float dt) = 0;

		float getWeight();
		int getMaxHP();
		int getCurrHP();
		std::string getType();

	private:
		float mWeight;
		float mMaxHP;
		std::string mType;
		float mMaxRepairHP;
		SpaceShip* mShip;

		std::list<dmgListener> dmgListenerList;
		float mCurrHP;

		void fireDmgChangeEvent(float dmg);

};

#endif // SHIPCOMPONENT_H_INCLUDED

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
<<<<<<< HEAD
		IComponent(irr::io::IAttributes& a, SpaceShip* myship );
=======

		IComponent(irr::io::IAttributes& a, SpaceShip* myship );
		virtual ~IComponent() = default;

		// non-virtual functions
>>>>>>> refs/remotes/origin/master
		float damage( float dam );
		void repair( float time_sec );
		dmgListenerPtr addDmgListener(dmgListener l);
		void removeDmgListener(dmgListenerPtr l_ptr);

<<<<<<< HEAD
		virtual float getStatus(std::string bez) = 0;
		virtual void step(float time_sec) = 0;
		virtual void onDamage(float dam) = 0;
		virtual int actionPerformed(int ctrlbits, float dt) = 0;

=======
>>>>>>> refs/remotes/origin/master
		float getWeight();
		int getMaxHP();
		int getCurrHP();
		std::string getType();

<<<<<<< HEAD
=======
		// virtual functions
		virtual float getStatus(std::string bez) = 0;
		virtual void step(float time_sec) = 0;
		virtual void onDamage(float dam) = 0;
		virtual int actionPerformed(int ctrlbits, float dt) = 0;

>>>>>>> refs/remotes/origin/master
	private:
		float mWeight;
		float mMaxHP;
		std::string mType;
		float mMaxRepairHP;
		SpaceShip* mShip;
<<<<<<< HEAD
		std::list<dmgListener> dmgListenerList;
		float mCurrHP;
=======
		std::list<dmgListener> mDmgListenerList;
		float mCurrHP;

>>>>>>> refs/remotes/origin/master
		void fireDmgChangeEvent(float dmg);

};

#endif // SHIPCOMPONENT_H_INCLUDED
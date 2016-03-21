#ifndef SHIPCOMPONENT_H_INCLUDED
#define SHIPCOMPONENT_H_INCLUDED

#include <string>
#include <list>
#include <functional>
#include <irrlicht/IAttributes.h>

class ShipComponent
{
	class Spaceship;

	protected:
		using dmgListener = std::function<void(float)>;
		using dmgListenerPtr = std::list<dmgListener>::iterator;

	public:
		ShipComponent(irr::io::IAttributes& a, Spaceship* myship );

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
		Spaceship* mShip;
		std::list<dmgListener> dmgListenerList;
		float mCurrHP;
		void fireDmgChangeEvent(float dmg);

};

#endif // SHIPCOMPONENT_H_INCLUDED

#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "IComponent.h"

class IWeapon : IComponent
{

public:
	using stateListener = std::function<void(bool)>;
	using stateListenerPtr = std::list<stateListener>::iterator;

	IWeapon(/*const*/ irr::io::IAttributes& a, SpaceShip* ship);

	stateListenerPtr addStateListener(stateListener l);
	void removeStateListener(stateListenerPtr l_ptr);
	void fireDmgChangeEvent(bool isBusy);

	float getLoadingProgress();

private:
	float loadingProgress;
	bool mIsBusy;

	std::list<stateListener> stateListenerList;
};


#endif // WEAPON_H_INCLUDED

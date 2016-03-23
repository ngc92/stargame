#include "IWeapon.h"

IWeapon::IWeapon(/*const*/ irr::io::IAttributes& a, SpaceShip* ship):
			IComponent(a,ship),
			loadingProgress(0),
			mIsBusy(false)
{
}

float IWeapon::getLoadingProgress()
{
	return loadingProgress;
}

IWeapon::stateListenerPtr IWeapon::addStateListener(stateListener l)
{
	stateListenerList.push_back(l);
	return --stateListenerList.end();
}

void IWeapon::removeStateListener(stateListenerPtr l_ptr)
{
	stateListenerList.erase(l_ptr);
}

void IWeapon::fireDmgChangeEvent(bool isBusy)
{
	mIsBusy = isBusy;
	std::list<stateListener> workList = stateListenerList;
    for(auto& lst : workList)
	{
		lst(mIsBusy);
    }
}

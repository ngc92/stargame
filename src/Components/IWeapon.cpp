#include "IWeapon.h"

IWeapon::IWeapon(/*const*/ irr::io::IAttributes& a, SpaceShip* ship):
			IComponent(a,ship),
			loadingProgress(0),
<<<<<<< HEAD
			mIsBusy(false)
=======
			mIsBusy(false),
			currAmmoCount(0),
			maxAmmoCount(a.getAttributeAsFloat("maxAmmoCount") )
>>>>>>> refs/remotes/origin/master
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

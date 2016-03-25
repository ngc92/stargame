#include "IWeapon.h"

namespace game
{
	IWeapon::IWeapon(/*const*/ irr::io::IAttributes& a):
				IComponent(a),
				loadingProgress(0),
				mIsBusy(false),
				currAmmoCount(0),
				maxAmmoCount(a.getAttributeAsFloat("maxAmmoCount") )
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
}
#ifndef SHIPSTATUSCTRL_H_INCLUDED
#define SHIPSTATUSCTRL_H_INCLUDED

#include <vector>
#include "listener/listener.h"

namespace game
{
	class IGameObjectView;
}

namespace graphic
{
	class IShipStatusView;

	class ShipStatusControl
	{
	public:
		ShipStatusControl(IShipStatusView* view, const game::IGameObjectView& ship);
	private:
		IShipStatusView* mView;
		std::vector<ListenerRef> mListeners;
	};
}

#endif // SHIPSTATUSCTRL_H_INCLUDED

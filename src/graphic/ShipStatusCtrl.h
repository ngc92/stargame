#ifndef SHIPSTATUSCTRL_H_INCLUDED
#define SHIPSTATUSCTRL_H_INCLUDED

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
	};
}

#endif // SHIPSTATUSCTRL_H_INCLUDED

#ifndef TACTICALMAPCTRL_H_INCLUDED
#define TACTICALMAPCTRL_H_INCLUDED

#include <unordered_map>
#include "listener/listener.h"

namespace game
{
	class IGameWorldView;
	class IGameObjectView;
}

namespace graphic
{
	class ITacticalMapView;

	class TacticalMapCtrl
	{
	public:
		TacticalMapCtrl(ITacticalMapView* view, game::IGameWorldView& world);
		~TacticalMapCtrl();
	private:
		void addObject( game::IGameObjectView& object );

		ITacticalMapView* mView = nullptr;

		std::unordered_map<game::IGameObjectView*, ListenerRef> mRegisteredListeners;
		ListenerRef mSpawnListener;
	};
}


#endif // TACTICALMAPCTRL_H_INCLUDED

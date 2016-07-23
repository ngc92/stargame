#ifndef TEXTINTERFACE_H_INCLUDED
#define TEXTINTERFACE_H_INCLUDED

#include "game/IGameViewModule.h"
#include "game/fwd.h"
#include "listener/listener.h"

class TextInterface : public game::IGameViewModule
{
public:
	void step( game::IGameWorldView& world_view ) override;
	void init( game::IGameWorldView& world_view ) override;
private:
	void onSpawn( const game::IGameObjectView& spawned );
	void handleObject( const game::IGameObjectView& view );

	ListenerRef mSpawnLst;

};

#endif // TEXTINTERFACE_H_INCLUDED

#ifndef TEXTINTERFACE_H_INCLUDED
#define TEXTINTERFACE_H_INCLUDED

#include "game/CGameViewModule.h"
#include "game/fwd.h"
#include "listener/listener.h"

class TextInterface : public game::CGameViewModule
{
public:
	void onStep() override;
	void init() override;
private:
	void onSpawn( const game::IGameObjectView& spawned );
	void handleObject( const game::IGameObjectView& view );
	
	ListenerRef mSpawnLst;

};

#endif // TEXTINTERFACE_H_INCLUDED

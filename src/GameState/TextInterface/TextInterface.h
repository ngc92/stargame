#ifndef TEXTINTERFACE_H_INCLUDED
#define TEXTINTERFACE_H_INCLUDED

#include "../IGameModule.h"

class TextInterface : public IGameModule
{
public:
	void onStep(const game::GameWorld& view) override;
	void onSpawn( const game::GameObject& spawned ) override;
private:
	void handleObject( const game::GameObject& view );

};

#endif // TEXTINTERFACE_H_INCLUDED

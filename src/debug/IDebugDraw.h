#ifndef IDEBUGDRAW_H_INCLUDED
#define IDEBUGDRAW_H_INCLUDED

#include "game/IGameViewModule.h"

class IDebugDraw : public virtual game::IGameViewModule
{
public:
	virtual ~IDebugDraw() = default;
	virtual void doDraw() const = 0;
};

#endif // IDEBUGDRAW_H_INCLUDED

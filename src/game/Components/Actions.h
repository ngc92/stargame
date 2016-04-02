#ifndef ACTIONS_H_INCLUDED
#define ACTIONS_H_INCLUDED

#include "IAction.h"

namespace game
{
	namespace actions
	{
		class Thrust;
		class ResourceRequest;
	}

	std::unique_ptr<IAction> makeThrustAction(const IComponent& src, b2Vec2 t, float r);
	std::unique_ptr<IAction> makeResourceRequestAction(IComponent& src, const std::string& res);
}

#endif // ACTIONS_H_INCLUDED

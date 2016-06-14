#ifndef IAIMODULE_H_INCLUDED
#define IAIMODULE_H_INCLUDED

#include "common_includes.h"

namespace game
{
	class IPropulsionSystem;
	namespace ai
	{
		class MicroAI;
	}

	class IAIModule : public IGameObjectModule
	{
	public:
        virtual std::shared_ptr<void> registerPropulsionSystem( IPropulsionSystem& sys ) = 0;
        virtual std::weak_ptr<ai::MicroAI> getAI() = 0;
	};
}


#endif // IAIMODULE_H_INCLUDED

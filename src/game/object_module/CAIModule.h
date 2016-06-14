#ifndef CAIMODULE_H_INCLUDED
#define CAIMODULE_H_INCLUDED


#include "util.h"
#include "IAIModule.h"

namespace game
{
	namespace ai
	{
		class MicroAI;
	}

	class CAIModule : public IAIModule, public property::CPropertyObject
	{
	public:
		CAIModule( );
		~CAIModule( );

		// Module functions
		void onStep( IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action) override;
		void onInit( IGameObject& object, IGameWorld& world ) override;

		std::shared_ptr<void> registerPropulsionSystem( IPropulsionSystem& sys ) override;
		std::weak_ptr<ai::MicroAI> getAI() override;
	private:
		std::shared_ptr<ai::MicroAI> mAI;
	};
}

#endif // CAIMODULE_H_INCLUDED

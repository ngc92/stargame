#include "CAIModule.h"
#include "game/AI/MicroAI.h"

namespace game
{
	CAIModule::CAIModule() : CPropertyObject("ai_module"),
		mAI( std::make_shared<ai::MicroAI>() )
	{

	}

	CAIModule::~CAIModule( )
	{

	}

	// Module functions
	void CAIModule::onStep( IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action)
	{
		mAI->act( object );
	}

	void CAIModule::onInit( IGameObject& object, IGameWorld& world )
	{

	}

	std::shared_ptr<void> CAIModule::registerPropulsionSystem( ai::IPropulsionSystem& sys )
	{
		return mAI->registerPropulsionSystem(sys);
	}

	std::weak_ptr<ai::MicroAI> CAIModule::getAI()
	{
		return mAI;
	}
}

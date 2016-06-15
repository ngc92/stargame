#include "CAIManager.h"
#include "MicroAI.h"
#include "game/IGameObject.h"
#include "game/IGameObjectModule.h"

namespace game
{
namespace ai
{
    void CAIManager::step()
    {
        for(auto& ai : mAIs)
		{
			ai.AI->act( *ai.target );
		}
    }

    std::shared_ptr<MicroAI> CAIManager::createAIFor( IGameObject& target )
    {
		auto pointer = std::dynamic_pointer_cast<IGameObject>(target.shared_from_this());
		mAIs.push_back({pointer, std::make_shared<MicroAI>()});
		for(auto& mod : target.modules())
		{
			mod->registerAtAI(*mAIs.back().AI);
		}
		return mAIs.back().AI;
    }
}
}

#include "CAIManager.h"
#include "MicroAI.h"
#include "game/IGameObject.h"
#include "game/IGameObjectModule.h"

namespace game
{
namespace ai
{
	std::unique_ptr<IAIManager> createDefaultAIManager()
	{
		return std::make_unique<CAIManager>();
	}

	// -------------------------------------------------

	void CAIManager::step()
	{
		mStepCount += 1;
		for(unsigned i = 0; i < mAIs.size(); ++i)
		{
			// only update every mUpdateInterval'th step, but interleave
			if( (i + mStepCount) % mUpdateInterval == 0 && mAIs[i].target->isAlive())
				mAIs[i].AI->act( *mAIs[i].target );
		}

		// remove AIs of dead ships
		auto nlast = std::remove_if(begin(mAIs), end(mAIs),
									[](const auto& ai){ return !ai.target->isAlive(); }
									);

		mAIs.resize(std::distance(begin(mAIs), nlast));
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

#ifndef CAIMANAGER_H_INCLUDED
#define CAIMANAGER_H_INCLUDED

#include "IAIManager.h"
#include <memory>
#include <vector>

namespace game
{
class IGameObject;
namespace ai
{
	class MicroAI;

	struct RegisteredAI
	{
		std::shared_ptr<IGameObject> target;
		std::shared_ptr<MicroAI> AI;
	};


    /*! \brief Implementation of an AI manager
		\details This AI manager keeps a vector of all active AIs,
			along with shared_ptr to their controlled objects.
     */
	class CAIManager : public IAIManager
	{
	public:
		void step() override;

		std::shared_ptr<MicroAI> createAIFor( IGameObject& target ) override;
	private:
		std::vector<RegisteredAI> mAIs;
	};
}
}

#endif // CAIMANAGER_H_INCLUDED

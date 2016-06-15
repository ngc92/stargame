#ifndef IAIMANAGER_H_INCLUDED
#define IAIMANAGER_H_INCLUDED

#include <memory>

namespace game
{
class IGameObject;
namespace ai
{
	class MicroAI;

	/*! \class IAIManager
		\brief Class that owns all AI objects and ensures they
				are properly stepped.
	*/
	class IAIManager
	{
	public:
		virtual ~IAIManager() = default;

		virtual void step() = 0;
		virtual std::shared_ptr<MicroAI> createAIFor( IGameObject& target ) = 0;
	};
}
}

#endif // IAIMANAGER_H_INCLUDED

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
		/// \todo later on, the MicroAI should not be visible to the end user.
		virtual std::shared_ptr<MicroAI> createAIFor( IGameObject& target ) = 0;
	};

	/// this function returns an IAManager object.
	std::unique_ptr<IAIManager> createDefaultAIManager();
}
}

#endif // IAIMANAGER_H_INCLUDED

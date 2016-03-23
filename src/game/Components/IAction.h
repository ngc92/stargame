#ifndef IACTION_H_INCLUDED
#define IACTION_H_INCLUDED

#include "util.h"
#include "game/fwd.h"

namespace game
{
	class IComponent;

	/*! \class IAction
		\brief Interface for actions that can be performed by components.
		\details This interface defines how components can communicate their
				intended actions towards the outside world. If a component
				wants to e.g. change the state of the spaceship, it needs
				to create the corresponding action.

				This class offers several act methods, that allow actions to
				affect different elements of the game environment. All these
				methods return a bool, which has to be true if the processing
				of this action is finished.

				Possible actions could be:
					Thrust for the engine/nozzles
					Spawn?/Shoot? for weapons
	*/
	class IAction
	{
	public:
		virtual ~IAction() = default;

		virtual const IComponent& getSource() = 0;

		virtual bool act( game::FlightModel& ) { return false; };
		virtual bool act( IComponent& ) { return false; };
	};

	/*! \class IActionListInterface
		\brief Basic interface of the action list.
		\details This is the interface that is passed down to the
				components and offers the ability to add actions.
	*/
	class IActionListInterface
	{
	public:
		virtual ~IActionListInterface() = default;

		virtual void push(std::unique_ptr<IAction>) = 0;

		template<class T, class... Args>
		void push(Args&&... args)
		{
			push(make_unique<T>(std::forward<Args>(args)...));
		}
	};
}
#endif // IACTION_H_INCLUDED

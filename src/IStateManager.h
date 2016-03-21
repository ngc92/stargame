#ifndef ISTATEMANAGER_H_INCLUDED
#define ISTATEMANAGER_H_INCLUDED

#include <string>
#include <functional>
#include <irrlicht/IEventReceiver.h>
#include "util.h"

class IState;

/*! \class IStateManager
    \brief manages IState objects
    \details this class is responsible for creating and deleting IStateObjects, deciding which one is the active one, which ones are
            drawn. States are organised in a stack, it is possible to switch to a new state, and once that is finsihed, return to
            the old one.
*/
class IStateManager : public noncopyable, ObjectCounter<IStateManager>
{
	protected:
		typedef std::function<std::shared_ptr<IState>(const irr::io::IAttributes&)> factory_fptr;

	public:
		virtual ~IStateManager() {};

		/// is called every frame and calles the step callback of active states.
		/// Returns false when no active state exists.
		virtual bool step() = 0;

		/// gets the current state.
		virtual IState* getCurrentState() const noexcept = 0;

		/// delete the current state and go back to the one below (in the state stack)
		virtual void deleteCurrentState() = 0;

		/// creates a new state an pushes it onto the state stack.
		virtual IState* createState(std::string name, const irr::io::IAttributes& param) = 0;

		/// creates a new state and replaces the old one.
		/// if the new state cannot be created, the old state is left intact (onDeactivate and onActivate called).
		/// the new state is created after onDeactivate for the old one is called, but before it is deleted.
		virtual void switchState(std::string name, const irr::io::IAttributes& param) noexcept = 0;

		///// sets a new state as active state
		//virtual void pushState(std::shared_ptr<IState> state) = 0;

		/// adds a factory function for the creation of states with a certain name.
		/// \exception Throws std::runtime_error if there already exists a fatory for
		///				the given name.
		virtual void addFactory(std::string name, factory_fptr factory) = 0;

		/// this function gets irrlicht gui events and passes them to the currently active gui manager
		/// \todo later, we could have gui manager layers and actually pass them down till one manager decides to process it
		virtual bool onEvent(irr::SEvent::SGUIEvent event) = 0;
};

#endif // ISTATEMANAGER_H_INCLUDED

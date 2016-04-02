#ifndef CSTATEMANAGER_H_INCLUDED
#define CSTATEMANAGER_H_INCLUDED

#include "IStateManager.h"
#include <stack>
#include <unordered_map>

class IEngine;

class CStateManager : public IStateManager
{
	public:
		CStateManager(IEngine* engine);
		~CStateManager();

		/// is called every frame and calles the step callback of active states.
		/// Returns false when no active state exists.
		bool step() override;

		/// gets the current state.
		IState* getCurrentState() const noexcept override;

		/// delete the current state and return to the one below
		void deleteCurrentState() override;

		/// creates a new state an pushes it onto the state stack.
		IState* createState(std::string name, const irr::io::IAttributes* param) override;

		/// creates a new state and replaces the old one.
		void switchState(std::string name, const irr::io::IAttributes* param) noexcept override;

		///// sets a new state as ative state
		//void pushState(std::shared_ptr<IState> state) override;

		/// adds a factory function for the creation of states with a certain name.
		/// \exception Throws std::runtime_error if there already exists a fatory for
		///				the given name.
		void addFactory(std::string name, factory_fptr factory) override;

		/// this function gets irrlicht gui events and passes them to the currently active gui manager
		bool onEvent(irr::SEvent::SGUIEvent event) override;

	private:
		std::stack<std::shared_ptr<IState>> mStateStack;
		std::unordered_map<std::string, factory_fptr> mFactories;

		IEngine* mEngine;
};


#endif // CSTATEMANAGER_H_INCLUDED

#include "CStateManager.h"
#include "IState.h"
#include "IEngine.h"
#include "IGUIManager.h"

#include "util.h"
#include <stdexcept>
#include <boost/exception/diagnostic_information.hpp>

CStateManager::CStateManager(IEngine* engine): mEngine(engine)
{

}

bool CStateManager::step()
{
	if(mStateStack.empty())
		return false;

	// temp copy of the state pointer, to make sure it is not deleted mid-step
	auto KEEP_ALIVE_TILL_END_OF_STEP = mStateStack.top();

	mStateStack.top()->update();
	return true;
}

IState* CStateManager::getCurrentState() const noexcept
{
	if(mStateStack.empty())
		return nullptr;

	return mStateStack.top().get();
}

void CStateManager::deleteCurrentState()
{
	getCurrentState()->onDeactivate();
	mStateStack.pop();

	if(getCurrentState())
		getCurrentState()->onActivate();
}

IState* CStateManager::createState(std::string name, const irr::io::IAttributes&  param)
{
	if(!mStateStack.empty())
		getCurrentState()->onDeactivate();

	auto factory = mFactories.find(name);
	std::shared_ptr<IState> state = nullptr;
	if(factory == mFactories.end())
	{
		LOG_ERROR(ELogCategory::STATE, " could not find factory function for state %name");
	}
	else
	{
		state = (factory->second)(param);
	}

	// push state to state stack before activating, so it is set as active state in this method
	mStateStack.push( state );
	// this means that if something goes wrong during the activation, we have to remove the state again.
	try
	{
		state->onActivate();
	}
	 catch (...)
	{
		mStateStack.pop();
		throw;
	}

	return state.get();
}

void CStateManager::switchState(std::string name, const irr::io::IAttributes& param) noexcept
{
	// save old state, so in case the creation of the new one does not work, we can restore it
	auto old = mStateStack.top();

	// deactivate old state and remove from state stack
	getCurrentState()->onDeactivate();
	mStateStack.pop();
	try
	{
		createState(name, param);
	}
	 catch (std::exception& ex)
	{
		/// \todo false log category
		LOG_ERROR(ELogCategory::STATE, "Could not switch to state " + name + ". Exception: " + boost::diagnostic_information(ex));

		// revert
		mStateStack.push(old);
		old->onActivate();
	}
}

/*void CStateManager::pushState(std::shared_ptr<IState> state)
{
	if(getCurrentState())
		getCurrentState()->onDeactivate();

	state->onActivate();
	mStateStack.push( state );
}
*/
void CStateManager::addFactory(std::string name, factory_fptr factory)
{
	if(mFactories.count(name))
	{
		throw std::runtime_error("Factory function " + name + " already exists!");
	}

	mFactories.insert( {name, factory} );
}

bool CStateManager::onEvent(irr::SEvent::SGUIEvent event)
{
	return getCurrentState()->getGUIManager()->onEvent(event);
}


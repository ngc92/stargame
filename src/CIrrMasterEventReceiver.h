#ifndef CIRRMASTEREVENTRECEIVER_H_INCLUDED
#define CIRRMASTEREVENTRECEIVER_H_INCLUDED

#include <irrlicht/IEventReceiver.h>
#include "util.h"

class IInputManager;
class IStateManager;
namespace irr
{
	class IrrlichtDevice;
}

/*! \class CIrrMasterEventReceiver
	\brief Event Receiver used by PRPGE to dispatch irrlicht events
	\details This class is set s irrlichts event receiver, gets all irrlicht events with it's
			OnEvent function and relays all input to input manager and all gui related messages
			to the gui manager of the currently active state.
*/
class CIrrMasterEventReceiver final : public irr::IEventReceiver
{
	public:
		/// create the event receiver
		/// \param ipmgr input manager that gets alls input events
		/// \param statemgr State manager, for getting active state
		/// \param logmgr log manager for logging purposes
		CIrrMasterEventReceiver(IInputManager* ipmgr,
								IStateManager* statemgr);

		/// called by the irrlicht engine when an event happened
		/// sends the event to the responsible subsystem.
		virtual bool OnEvent(const irr::SEvent& event) override;

		/// sets the irrlicht device
		void setDevice(irr::IrrlichtDevice* dev);

	private:

		bool dispenseEvent(const irr::SEvent& event);

		IInputManager* mInputManager;
		IStateManager* mStateManager;
		irr::IrrlichtDevice* mDevice;
};


#endif // CIRRMASTEREVENTRECEIVER_H_INCLUDED

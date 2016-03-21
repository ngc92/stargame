#ifndef IENGINE_H_INCLUDED
#define IENGINE_H_INCLUDED

#include "util.h"

class IInputManager;
class IGUIManager;
class IDebugDrawer;
class IStateManager;
class ISoundManager;
class Options;

/*! \class IEngine
	\brief Base class of stargame
	\details This class manages all global stargame objects. It provides access functions
			and system event functions tick() and init()
*/
class IEngine : public ObjectCounter<IEngine>, noncopyable
{
	public:
		/// virtual dtor
		virtual ~IEngine() noexcept {};

		/// init function. has to be called before any call to tick.
		/// creates the graphic device (e.g. Irrlicht device)
		virtual bool init(const Options& options) = 0;

		/// has to be called every time step. updates the engine. returns
		/// false if the main window was closed and the program should quit.
		virtual bool tick() = 0;

		// get global manager etc.
		/// \todo maybe we don't want all of these as global at all, e.g, sometimes
		/// 2 physic worlds would come handy
		/// gets the input manager
		virtual IInputManager& getInputManager() = 0;
		/// gets the input manager (const)
		virtual const IInputManager& getInputManager() const = 0;

		/// creates a gui manager
		virtual IGUIEnvironment* getGUIEnvironment() const = 0;

		/// gets state manager
		virtual IStateManager& getStateManager() = 0;
		/// gets state manager (const)
		virtual const IStateManager& getStateManager() const = 0;

		/// gets sound manager
		virtual ISoundManager& getSoundManager() = 0;
		/// gets sound manager (const)
		virtual const ISoundManager& getSoundManager() const = 0;
};

#endif // IENGINE_H_INCLUDED

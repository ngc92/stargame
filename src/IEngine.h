#ifndef IENGINE_H_INCLUDED
#define IENGINE_H_INCLUDED

#include "util.h"

class IInputManager;
class IGameWorld;
class IGraphixManager;
class IGUIManager;
class IDebugDrawer;
class ILogManager;
class IStateManager;

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
		virtual bool init(bool dbdraw) = 0;

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
		virtual std::shared_ptr<IGUIManager> createGUIManager() const = 0;

		/// gets the graphic manager
		virtual IGraphixManager& getGraphixManager() = 0;
		/// gets the graphic manager (const)
		virtual const IGraphixManager& getGraphixManager() const = 0;

		/// gets debug drawer
		virtual IDebugDrawer& getDebugDrawer() = 0;
		/// gets debug drawer (const)
		virtual const IDebugDrawer& getDebugDrawer() const = 0;

		/// gets state manager
		virtual IStateManager& getStateManager() = 0;
		/// gets state manager (const)
		virtual const IStateManager& getStateManager() const = 0;

		/// gets Log manager
		virtual ILogManager& getLogManager() = 0;
		virtual const ILogManager& getLogManager() const = 0;

		// conveninece function: relays work to level loader
		virtual std::shared_ptr<IGameWorld> loadLevel(const std::string& filename) = 0;

		virtual std::shared_ptr<IGameWorld> createLevel() = 0;
};

#endif // IENGINE_H_INCLUDED

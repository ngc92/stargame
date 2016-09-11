#ifndef IGAMEWORLD_H_INCLUDED
#define IGAMEWORLD_H_INCLUDED

#include "IGameWorldView.h"
#include "IGameObject.h" // we need this for covariant return
#include <boost/optional.hpp>

namespace game
{
	class IGameModule;

	namespace spawn
	{
		class ISpawnManager;
	}

	/*! \class IGameWorld
		\brief Game World, manages Game Objects and physics.
	*/
	class IGameWorld : public IGameWorldView
	{
	public:
		/// perform a single step in the game simulation.
		virtual void step( const spawn::ISpawnManager& spawner ) = 0;

		/// adds a game object to the game world.
		virtual void addGameObject(std::shared_ptr<IGameObject> object) = 0;

		/// get a game object with specified id.
		/// \throw If object not found. For non-throwing, use the pointer version.
		virtual IGameObject& getObjectByID( uint64_t id ) = 0;
		
		/// get the game object view with specified id.
		virtual IGameObject* getObjectPtrByID( uint64_t id ) = 0;
		
		/// get a game object view with specified name. If more than
		/// one object exists with the given name, it is unspecified 
		/// which one is returned (i.e. don't do that!).
		virtual IGameObject& getObjectByName( const std::string& name ) = 0;
		
		/// gets an id that is currently not used by any game object.
		/// \note currently not marked as const, because the internal id cache may be changed.
		virtual uint64_t getNextFreeID() = 0;

		/// Adds a module to this worlds module list.
		/// the module is removed as soon as that weak_ptr
		/// expires.
		/// The module is directly initialized.
		virtual void addModule(std::weak_ptr<IGameModule> module) = 0;
		using IGameWorldView::addModule;
	};
	
	/// creates an IGameWorld object using the simulation implementation.
	std::unique_ptr<IGameWorld> createSimulationWorld();
	
	/// creates an IGameWorld object using the observation implementation.
	std::unique_ptr<IGameWorld> createObservationWorld();
}

#endif // IGAMEWORLD_H_INCLUDED

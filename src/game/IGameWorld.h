#ifndef IGAMEWORLD_H_INCLUDED
#define IGAMEWORLD_H_INCLUDED

#include "IGameWorldView.h"

namespace game
{
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
		virtual IGameObject& getObjectByID( uint64_t id ) = 0;

		/// get a pointer to the internal world
		virtual const b2World* world() const = 0;

		/// get a pointer to the internal world
		virtual b2World* getWorld() = 0;
	};
	
	/// creates an IGameWorld object using the default implementation.
	std::unique_ptr<IGameWorld> createGameWorld();
}

#endif // IGAMEWORLD_H_INCLUDED

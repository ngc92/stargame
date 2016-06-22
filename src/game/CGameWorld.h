#ifndef CGAMEWORLD_H_INCLUDED
#define CGAMEWORLD_H_INCLUDED

#include "IGameWorld.h"
#include "listener/listenerlist.h"

namespace game
{
	class ContactListener;

	class CGameWorld : public IGameWorld
	{
	public:
		CGameWorld();

		~CGameWorld();

		/// iterates over all game objects \p o inside this world and calls \p f(o).
		void iterateAllObjects(const std::function<void(IGameObjectView&)>& f) const final;

		/// gets the number of objects that are currently registered in the world.
		std::size_t object_count() const final;

		/// adds a listener that is called whenever a new game objects is spawned in the world.
		ListenerRef addSpawnListener(std::function<void(IGameObjectView&)> f) final;

		/// perform a single step in the game simulation.
		void step( const spawn::ISpawnManager& spawner ) final;

		/// adds a game object to the game world.
		void addGameObject(std::shared_ptr<IGameObject> object) final;

		/// get a game object with specified id.
		IGameObject& getObjectByID( uint64_t id ) final;

		/// get a pointer to the internal world
		const b2World* world() const final;

		/// get a pointer to the internal world
		b2World* getWorld() final;

		/// Adds a module to this worlds module list.
		/// the module is removed as soon as that weak_ptr
		/// expires.
		/// The module is directly initialized.
		void addModule(std::weak_ptr<IGameViewModule> module) final;

		void addModule(std::weak_ptr<IGameModule> module) final;
	private:
		/// remove all objects marked for deletion.
		void clear_objects();

		std::unique_ptr<b2World> mPhysicWorld; 					//!< The Box2D physics world
		std::unique_ptr<ContactListener> mContactListener;		//!< The contact listener for Box2D

		std::vector<std::shared_ptr<IGameObject>> mGameObjects;	//!< Vector of all IGameObject in this world.
		std::vector<std::shared_ptr<IGameObject>> mSpawnQueue;	//!< Vector of all IGameObject that have to be spawned at the end of the step.

		ListenerList<IGameObject&> mSpawnListeners;				//! List of spawn listeners

		std::vector<std::weak_ptr<IGameModule>> mModules;			//! Vector of all registered game modules.
		std::vector<std::weak_ptr<IGameViewModule>> mViewModules;	//! Vector of all registered game view modules.

	};
}

#endif // CGAMEWORLD_H_INCLUDED

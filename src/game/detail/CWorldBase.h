#ifndef CGAMEWORLDBASE_H_INCLUDED
#define CGAMEWORLDBASE_H_INCLUDED


#include "../IGameWorld.h"
#include "listener/listenerlist.h"

namespace game
{
	class ContactListener;

	/*! \class CWorldBase
		\brief Base class for the default game world implementations.
		\details This class contains code that is common to both the
				simulation and the observation world.
	*/
	class CWorldBase : public IGameWorld
	{
	public:
		
		CWorldBase();
/*
		virtual ~CWorldBase();
*/
		/// iterates over all game objects \p o inside this world and calls \p f(o).
		void iterateAllObjects(const std::function<void(IGameObjectView&)>& f) const final;

		/// gets the number of objects that are currently registered in the world.
		std::size_t object_count() const final;

		/// adds a listener that is called whenever a new game objects is spawned in the world.
		ListenerRef addSpawnListener(std::function<void(IGameObjectView&)> f) final;

		/// adds a game object to the game world.
		void addGameObject(std::shared_ptr<IGameObject> object) final;

		/// get a game object with specified id.
		IGameObject& getObjectByID( uint64_t id ) final;

		/// get a pointer to the internal world
		const b2World& world() const final;
		
		b2World& getWorld() final;

		/// Adds a module to this worlds module list.
		/// the module is removed as soon as that weak_ptr
		/// expires.
		/// The module is directly initialized.
		void addModule(std::weak_ptr<IGameViewModule> module) final;
	
	protected:
		
		/// add all object from the spawn queue to the object list, and call the spawn listeners.
		void perform_spawning();
		
		/// remove all objects marked for deletion.
		void clear_objects();
		
		/// steps all view modules, and removes expired ones.
		void update_view_modules();
		
		/// steps all game objects, and removes expired ones.
		void update_game_objects(const spawn::ISpawnManager& spawner);
		
		// protected data.
/*		std::unique_ptr<ContactListener> mContactListener;		//!< The contact listener for Box2D
		
*/		std::vector<std::shared_ptr<IGameObject>> mGameObjects;	//!< Vector of all IGameObject in this world.
	private:
		std::unique_ptr<b2World> mPhysicWorld; 					//!< The Box2D physics world.
		std::vector<std::shared_ptr<IGameObject>> mSpawnQueue;	//!< Vector of all IGameObject that have to be spawned at the end of the step.
		ListenerList<IGameObject&> mSpawnListeners;				//! List of spawn listeners
		
		std::vector<std::weak_ptr<IGameViewModule>> mViewModules;	//! Vector of all registered game view modules.
	};
}


#endif // CGAMEWORLDBASE_H_INCLUDED

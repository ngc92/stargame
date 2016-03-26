#ifndef GAMEWORLD_H_INCLUDED
#define GAMEWORLD_H_INCLUDED

#include <Box2D/Dynamics/b2World.h>
#include <memory>
#include <vector>
#include "util/ListenerList.h"

namespace game
{
	class GameObject;
	class ContactListener;

	/*! \class GameWorld
		\brief Main class for the game world.
		\details
		\todo separate interface and implementation here!
	*/
	class GameWorld
	{
	public:
		GameWorld();
		~GameWorld();

		void step( float dt );

		void addGameObject(std::shared_ptr<GameObject> object);

		/// \todo we need to figure out where best to put this functionality
		b2Body* createBody(const b2BodyDef& );

		template<class T>
		void iterateViews(T&& f) const;

		template<class T>
		ListenerRef addSpawnListener(T&& f);
	private:
		/// remove all game objects that are no longer considered alive from the object list.
		void clear_objects();

		std::unique_ptr<b2World> mPhysicWorld;
		std::unique_ptr<ContactListener> mContactListener;
		std::vector<std::shared_ptr<GameObject>> mGameObjects;

		ListenerList<GameObject&> mSpawnListeners;
	};

	template<class T>
	void GameWorld::iterateViews(T&& f) const
	{
		for(auto& sp : mGameObjects)
		{
			const GameObject& obj = *sp;
			f(obj);
		}
	}

	template<class T>
	ListenerRef GameWorld::addSpawnListener(T&& f)
	{
		return mSpawnListeners.addListener(f);
	}
}

#endif // GAMEWORLD_H_INCLUDED

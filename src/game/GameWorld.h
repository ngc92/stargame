#ifndef GAMEWORLD_H_INCLUDED
#define GAMEWORLD_H_INCLUDED

#include <Box2D/Dynamics/b2World.h>
#include <memory>
#include <vector>

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


		template<class T>
		void iterateViews(T&& f) const;
	private:
		/// remove all game objects that are no longer considered alive from the object list.
		void clear_objects();

		std::unique_ptr<b2World> mPhysicWorld;
		std::unique_ptr<ContactListener> mContactListener;
		std::vector<std::shared_ptr<GameObject>> mGameObjects;
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
}

#endif // GAMEWORLD_H_INCLUDED

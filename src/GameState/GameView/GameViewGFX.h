#ifndef GAMEVIEWGFX_H_INCLUDED
#define GAMEVIEWGFX_H_INCLUDED

#include <string>
#include "listener/listener.h"
#include <irrlicht/vector3d.h>

namespace game
{
	class IGameObjectView;
}

namespace irr
{
	class IrrlichtDevice;

	namespace video
	{
		class IVideoDriver;
	}

	namespace scene
	{
		class ISceneManager;
		class ICameraSceneNode;
		class ISceneNode;
		class ISceneNodeAnimator;
	}
}

namespace gfx
{
	using namespace irr;

	class GameViewGFX
	{
	public:
		GameViewGFX(IrrlichtDevice* device);

		void init();
		/// \note takes object as nonconst reference because it has to add a remove listener.
		/// \return reference to the deletion listener of the object.
		ListenerRef addShip(game::IGameObjectView& object, int type );

		// let camera follow and track object

		// animators
		scene::ISceneNodeAnimator* createGameObjectAnimator( const game::IGameObjectView& object ) const;
		scene::ISceneNodeAnimator* createTrackAnimator( const scene::ISceneNode* target, float smoothness = 1 ) const;
		scene::ISceneNodeAnimator* createFollowAnimator( const scene::ISceneNode* target, float distance = 10,
														float smoothness = 1, float maxSpeed = 10,
														const core::vector3df& offset = core::vector3df(0,10,0)) const;

	private:

		video::IVideoDriver* mDriver = nullptr;
		scene::ISceneManager* mSceneMgr = nullptr;

		// camera configuration
		scene::ICameraSceneNode* mCamera = nullptr;
	};
}

#endif // GAMEVIEWGFX_H_INCLUDED

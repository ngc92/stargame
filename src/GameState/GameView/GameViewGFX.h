#ifndef GAMEVIEWGFX_H_INCLUDED
#define GAMEVIEWGFX_H_INCLUDED

#include <string>

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
		void addShip(const game::IGameObjectView* object, std::string type );
		
		// let camera follow and track object
		
		// animators
		scene::ISceneNodeAnimator* createGameObjectAnimator( const game::IGameObjectView* object ) const;
		scene::ISceneNodeAnimator* createTrackAnimator( const scene::ISceneNode* target, float smoothness = 1 ) const;
		scene::ISceneNodeAnimator* createFollowAnimator( const scene::ISceneNode* target, float distance = 10, float smoothness = 1, float maxSpeed = 10 ) const;
		
	private:
		
		
		video::IVideoDriver* mDriver = nullptr;
		scene::ISceneManager* mSceneMgr = nullptr;
		
		// camera configuration
		scene::ICameraSceneNode* mCamera = nullptr;
	};
}

#endif // GAMEVIEWGFX_H_INCLUDED

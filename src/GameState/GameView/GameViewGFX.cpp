#include "GameViewGFX.h"
#include "game/IGameObjectView.h"
#include "graphic/GameObjectAnimator.h"
#include "graphic/TrackObjectAnimator.h"
#include "graphic/FollowObjectAnimator.h"
#include "graphic/EngineExhaust.h"
#include <irrlicht/irrlicht.h>
#include <iostream>

namespace gfx
{
	using namespace irr;

	GameViewGFX::GameViewGFX(IrrlichtDevice* device) :
		mDriver(device->getVideoDriver()), mSceneMgr(  device->getSceneManager() )
	{
	}


	void GameViewGFX::init()
	{
		mCamera = mSceneMgr->addCameraSceneNode();
		mCamera->setFarValue(100000);

		//*********************************************************
		// create skybox
		mSceneMgr->addSkyBoxSceneNode  (
			mDriver->getTexture("gfx/kurt/space_up.png"), //top
			mDriver->getTexture("gfx/kurt/space_dn.png"), //bottom
			mDriver->getTexture("gfx/kurt/space_lf.png"), //left
			mDriver->getTexture("gfx/kurt/space_rt.png"), //right
			mDriver->getTexture("gfx/kurt/space_ft.png"), //front
			mDriver->getTexture("gfx/kurt/space_bk.png")  //back
		);

		// *********************************************************
		// dust effect
		auto dust = mSceneMgr->addParticleSystemSceneNode(false);
		scene::IParticleEmitter* emitter = dust->createBoxEmitter(
					core::aabbox3d<f32>(-500,-500,-500,500,500,500),	// emitter size
					core::vector3df(0.0f,0.01f,0.0f),	// initial direction
					80,100,								// emit rate
					video::SColor(255, 50, 50, 50),		// darkest color
					video::SColor(255,150,150,150),		// brightest color
					1000,2000,360,						// min and max age, angle
					core::dimension2df(0.5f,0.5f),		// min size
					core::dimension2df(2.f,2.f));		// max size

		dust->setEmitter(emitter); // this grabs the emitter
		dust->setMaterialFlag(video::EMF_LIGHTING, false);
		dust->setParent(mCamera);


		// *********************************************************
		// Background lighting
		mSceneMgr->setAmbientLight( video::SColorf(0.1, 0.1, 0.1, 0.1) );
		scene::ILightSceneNode* light = mSceneMgr->addLightSceneNode( mCamera );
		light->setLightType( video::ELT_DIRECTIONAL );
	}

	ListenerRef GameViewGFX::addShip( game::IGameObjectView& object, std::string type )
	{
		/// \todo this is caches, except when we cannot find the model. remember these.
		auto mesh = mSceneMgr->getMesh( ("gfx/models/" + type + ".3ds").c_str() );
		if(!mesh)
			return ListenerRef();

		auto node = mSceneMgr->addMeshSceneNode( mesh );
		node->addAnimator( createGameObjectAnimator(object) );
		
		// add the engine effect
		auto exhaust = new gfx::EngineExhaustNode(node, node->getSceneManager(), -1, 1, 1, true);
		exhaust->addNozzle(core::vector3df(0,0,0));

		auto ref = object.addRemoveListener( [node](){ node->remove(); } );

		static bool f = true;
		if(f)
		{
			mCamera->addAnimator( createTrackAnimator(node) );
			mCamera->addAnimator( createFollowAnimator(node, 15, 0.1, 100) );
			f = false;
		}

		return ref;
	}

	scene::ISceneNodeAnimator* GameViewGFX::createGameObjectAnimator( const game::IGameObjectView& object ) const
	{
		return new gfx::GameObjectAnimator( object );
	}

	scene::ISceneNodeAnimator* GameViewGFX::createTrackAnimator( const scene::ISceneNode* target, float smoothness ) const
	{
		return new gfx::TrackObjectAnimator(target, smoothness);
	}

	scene::ISceneNodeAnimator* GameViewGFX::createFollowAnimator( const scene::ISceneNode* target, float distance, float smoothness, float maxSpeed) const
	{
		return new gfx::FollowObjectAnimator(target, distance, smoothness, maxSpeed, vector3df(0,10,0));
	}
}

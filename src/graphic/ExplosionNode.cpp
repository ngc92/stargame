#include "ExplosionNode.h"
#include <irrlicht/irrlicht.h>
<<<<<<< HEAD
#include <iostream>
=======

>>>>>>> refs/remotes/origin/master
using namespace irr::video;

namespace gfx
{
<<<<<<< HEAD
	ExplosionNode::ExplosionNode(ISceneNode* parent, ISceneManager *mgr, s32 id, float intensity):
				ISceneNode(parent, mgr, id),
				mGenerationTimer(100),
				mLastTime(-1),
				mIntensity( intensity )
=======
	ExplosionNode::ExplosionNode(ISceneNode* parent, ISceneManager *mgr, s32 id,
								float intensity, video::ITexture* fire_tex):
				ISceneNode(parent, mgr, id),
				mGenerationTimer(100),
				mLastTime(-1),
				mIntensity( intensity ),
				mFireTexture( fire_tex )
>>>>>>> refs/remotes/origin/master
	{
		mLight = mgr->addLightSceneNode(this, core::vector3df(0,0,0), SColorf(1.0, 0.7, 0.25), 500);
		mLight->setLightType( video::ELT_POINT );

<<<<<<< HEAD
		mFire = SceneManager->addParticleSystemSceneNode(false, this, 0, irr::core::vector3df(0,0, 00));
=======
		mFire = SceneManager->addParticleSystemSceneNode(false, this, 0, irr::core::vector3df(0,0, 0));
>>>>>>> refs/remotes/origin/master
		mFire->setParticleBehavior( EPB_EMITTER_VECTOR_IGNORE_ROTATION | EPB_EMITTER_FRAME_INTERPOLATION);
		mFire->setParticlesAreGlobal(true);

		//Emitter
		mEmitter = mFire->createSphereEmitter(
<<<<<<< HEAD
				vector3df(0,0,0), 10, vector3df(1 * mIntensity,0,0), 1000, 2000,
=======
				vector3df(0,0,0), 10, vector3df(1 * mIntensity, 0, 0), 1000, 2000,
>>>>>>> refs/remotes/origin/master
				SColor(0,255,255,255), SColor(0,255,255,255),
				200 * mIntensity, 400 * mIntensity, 360,
				dimension2df(20.0f * mIntensity,20.0f *mIntensity), dimension2df(30.0f * mIntensity, 30.0f * mIntensity));

		mFire->setEmitter(mEmitter);

		IParticleAffector* paf = mFire->createFadeOutParticleAffector(SColor(0,0,0,0), 500);
		mFire->addAffector(paf);
	    paf->drop();

	    paf = mFire->createScaleParticleAffector(dimension2df(150, 150));
		mFire->addAffector(paf);
	    paf->drop();

		auto delani = mgr->createDeleteAnimator(2000);
	    addAnimator( delani );
	    delani->drop();

		mFire->setMaterialFlag(EMF_LIGHTING, false);
<<<<<<< HEAD
		mFire->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("fire.png"));
=======
		mFire->setMaterialTexture(0, mFireTexture);
>>>>>>> refs/remotes/origin/master
		mFire->setMaterialType(/*EMT_TRANSPARENT_VERTEX_ALPHA*/EMT_TRANSPARENT_ADD_COLOR);
	}

	ExplosionNode::~ExplosionNode()
	{

	}

	void ExplosionNode::OnAnimate(u32 timeMs)
	{
		ISceneNode::OnAnimate(timeMs);
		if(mLastTime != -1)
			mGenerationTimer -= timeMs - mLastTime;
		mLastTime = timeMs;
		float rad = 600 + mGenerationTimer*4;
		if( rad > 0)
			mLight->setRadius( rad );

		if( mGenerationTimer < 0)
		{
			mEmitter->setMaxParticlesPerSecond(0);
			mEmitter->setMinParticlesPerSecond(0);
<<<<<<< HEAD

		}
	}

=======
		}
	}

	const core::aabbox3d<f32>& ExplosionNode::getBoundingBox() const
	{
        return mFire->getBoundingBox();
	}

>>>>>>> refs/remotes/origin/master
	void ExplosionNode::render()
	{
	}

	void ExplosionNode::OnRegisterSceneNode()
	{
		ISceneNode::OnRegisterSceneNode();
	}
<<<<<<< HEAD
=======

	f32 ExplosionNode::getIntensity() const
	{
		return mIntensity;
	}

	video::ITexture* ExplosionNode::getTexture() const
	{
		return mFireTexture;
	}
>>>>>>> refs/remotes/origin/master
}

#include "ExplosionNode.h"
#include <irrlicht/irrlicht.h>

using namespace irr::video;

namespace gfx
{

	ExplosionNode::ExplosionNode(ISceneNode* parent, ISceneManager *mgr, s32 id,
								float intensity, video::ITexture* fire_tex):
				ISceneNode(parent, mgr, id),
				mGenerationTimer(100),
				mLastTime(-1),
				mIntensity( intensity ),
				mFireTexture( fire_tex )

	{
		mLight = mgr->addLightSceneNode(this, core::vector3df(0,0,0), SColorf(1.0, 0.7, 0.25), 500);
		mLight->setLightType( video::ELT_POINT );


		mFire = SceneManager->addParticleSystemSceneNode(false, this, 0, irr::core::vector3df(0,0, 0));

		mFire->setParticleBehavior( EPB_EMITTER_VECTOR_IGNORE_ROTATION | EPB_EMITTER_FRAME_INTERPOLATION);
		mFire->setParticlesAreGlobal(true);

		//Emitter
		mEmitter = mFire->createSphereEmitter(

				vector3df(0,0,0), 10, vector3df(1 * mIntensity, 0, 0), 1000, 2000,

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

		mFire->setMaterialTexture(0, mFireTexture);

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

		}
	}

	const core::aabbox3d<f32>& ExplosionNode::getBoundingBox() const
	{
        return mFire->getBoundingBox();
	}

	void ExplosionNode::render()
	{
	}

	void ExplosionNode::OnRegisterSceneNode()
	{
		ISceneNode::OnRegisterSceneNode();
	}


	f32 ExplosionNode::getIntensity() const
	{
		return mIntensity;
	}

	video::ITexture* ExplosionNode::getTexture() const
	{
		return mFireTexture;
	}
}

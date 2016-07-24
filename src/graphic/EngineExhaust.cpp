#include "EngineExhaust.h"
#include "util.h"
#include <irrlicht/ISceneManager.h>
#include <irrlicht/ILightSceneNode.h>

using namespace irr::video;

namespace gfx
{
	EngineExhaustNode::EngineExhaustNode(ISceneNode* parent, ISceneManager *mgr, s32 id,
										float radius, float psize, bool light):
				ISceneNode(parent, mgr, id),
				mParticleSize(psize),
				mExhaustVelocity(-0.02, 0, 0),
				mRadius(radius)
	{

		// engine light
		if(light)
		{
			scene::ILightSceneNode* light = mgr->addLightSceneNode(this, core::vector3df(0,0,40), SColorf(0.6, 0.4, 0.1), 30);
			light->setLightType( video::ELT_POINT );
		}

		// create particle system to set up affectors, then delete  again
		/// \todo fix this
		auto fire = SceneManager->addParticleSystemSceneNode(false, 0, 0);
		//Emitter
		mFadeOutAffector = fire->createFadeOutParticleAffector(SColor(0,0,0,0), mParticleLifetime );
		mScaleAffector = fire->createScaleParticleAffector(dimension2df(4.0 * psize , 4.0 * psize ));
		fire->remove();

		// texture loading
		mFireTexture = SceneManager->getVideoDriver()->getTexture("gfx/fire.png");
		if(mFireTexture)
			mFireTexture->grab();

		setName("engine");
	}

	EngineExhaustNode::~EngineExhaustNode()
	{
		if(mFireTexture)
			mFireTexture->drop();
		mFadeOutAffector->drop();
		mScaleAffector->drop();
	}

	void EngineExhaustNode::addNozzle( irr::core::vector3df offset )
	{
		auto fire = SceneManager->addParticleSystemSceneNode(false, this, 0);
		fire->setParticleBehavior( EPB_EMITTER_VECTOR_IGNORE_ROTATION | EPB_EMITTER_FRAME_INTERPOLATION);

		fire->setParticlesAreGlobal(true);

		//Emitter
		auto emitter = fire->createSphereEmitter(
				offset, mRadius, vector3df(0,0,-1), 20, 20,
				SColor(255,255,255,255), SColor(255,255,255,255),
				mParticleLifetime - 100, mParticleLifetime, 5, dimension2df(mParticleSize, mParticleSize), dimension2df( mParticleSize * 1.5, mParticleSize * 1.5));

		fire->setEmitter(emitter);

		fire->addAffector(mFadeOutAffector);
		fire->addAffector(mScaleAffector);

		fire->setMaterialFlag(EMF_LIGHTING, false);
		fire->setMaterialTexture(0, mFireTexture);
		fire->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
		//fire->setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );

		mFireEmitters.push_back( fire );
	}

	void EngineExhaustNode::OnAnimate(u32 timeMs)
	{
		ISceneNode::OnAnimate(timeMs);

		auto vec = mExhaustVelocity;
		getAbsoluteTransformation().rotateVect(vec);

		for(auto fire : mFireEmitters )
		{
			fire->getEmitter()->setDirection( vec + mShipVelocity );
		}
	}

	void EngineExhaustNode::render()
	{
	}

	const core::aabbox3d<f32>& EngineExhaustNode::getBoundingBox() const
	{
		return mFireEmitters[0]->getBoundingBox();
	}

	// configuration options
	void EngineExhaustNode::setParticleSize( f32 size )
	{
		mParticleSize = size;
		/// \todo change size of emitters and animators
	}

	void EngineExhaustNode::setParticleLifetime( u32 lifetime )
	{
		mParticleLifetime = lifetime;
		mFadeOutAffector->setFadeOutTime( lifetime );
	}

	void EngineExhaustNode::setParticleCount( u32 max_particles )
	{
		mMaxParticles = max_particles;
	}

	void EngineExhaustNode::setIntensity( float intensity )
	{
		double pcount = mMaxParticles * (0.75*intensity+0.25) / mFireEmitters.size();

		for(auto fire : mFireEmitters )
		{
			fire->getEmitter()->setMaxParticlesPerSecond( int( pcount ) );
			fire->getEmitter()->setMinParticlesPerSecond( int( pcount * 0.75 ) );
		}
	}

	void EngineExhaustNode::setOverrideTexture( video::ITexture* texture, video::E_MATERIAL_TYPE material )
	{
		if(!texture)
			return;

		mFireTexture->drop();
		mFireTexture = texture;

		for(auto fire : mFireEmitters )
		{
			fire->setMaterialTexture(0, mFireTexture);
			fire->setMaterialType( material );
		}
	}

	void EngineExhaustNode::setExhaustVelocity( core::vector3df velocity )
	{
		// convert to per millisecond and set
		mExhaustVelocity = 0.001 * velocity;
	}

	void EngineExhaustNode::setShipVelocity( core::vector3df velocity )
	{
		// convert to per millisecond and set
		mShipVelocity = 0.001 * velocity;
	}

	void EngineExhaustNode::OnRegisterSceneNode()
	{
		ISceneNode::OnRegisterSceneNode();
	}
}

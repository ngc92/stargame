#include "EngineExhaust.h"
#include "util.h"
#include <irrlicht/ISceneManager.h>
#include <irrlicht/ILightSceneNode.h>

using namespace irr::video;

const int PARTICLE_LIFETIME = 800;

namespace gfx
{
	EngineExhaustNode::EngineExhaustNode(ISceneNode* parent, ISceneManager *mgr, s32 id,
										float radius, float psize, bool light):
				ISceneNode(parent, mgr, id),
				mIntensity(0),
				mDamageFactor(1),
				mBaseVelocity(0,0),
				mRadius(radius),
				mParticleSize(psize)
	{

		// engine light
		if(light)
		{
			scene::ILightSceneNode* light = mgr->addLightSceneNode(this, core::vector3df(0,0,40), SColorf(0.6, 0.4, 0.1), 30);
			light->setLightType( video::ELT_POINT );
		}

		// create particle system to set up affectors, then delete  again
<<<<<<< HEAD
=======
		/// \todo fix this
>>>>>>> refs/remotes/origin/master
		auto fire = SceneManager->addParticleSystemSceneNode(false, 0, 0);
		fire->setParticleBehavior( scene::EPB_EMITTER_VECTOR_IGNORE_ROTATION | scene::EPB_EMITTER_FRAME_INTERPOLATION);
		//Emitter
		mFadeOutAffector = fire->createFadeOutParticleAffector(SColor(0,0,0,0), PARTICLE_LIFETIME - 100);
		mScaleAffector = fire->createScaleParticleAffector(dimension2df(4.0 * psize , 4.0 * psize ));
		fire->remove();

		// texture loading
		mFireTexture = SceneManager->getVideoDriver()->getTexture("fire.png");
		mFireTexture->grab();

		setName("engine");
	}

	EngineExhaustNode::~EngineExhaustNode()
	{
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
				PARTICLE_LIFETIME-100, PARTICLE_LIFETIME, 5, dimension2df(mParticleSize, mParticleSize), dimension2df( mParticleSize * 1.5, mParticleSize * 1.5));

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

		const float PARAMETER = 1.75;

		double pcount = PARAMETER*mIntensity / mFireEmitters.size();

		for(auto fire : mFireEmitters )
		{
			fire->getEmitter()->setDirection( b2i(PARAMETER*mThrustVector + mBaseVelocity) );
			fire->getEmitter()->setMaxParticlesPerSecond( int(pcount * 180.0f) );
			fire->getEmitter()->setMinParticlesPerSecond( int(pcount * 150.0f) );
		}
	}

	void EngineExhaustNode::render()
	{
	}

	void EngineExhaustNode::setIntensity( float cs )
	{
		mIntensity = cs;
	}

	void EngineExhaustNode::setThrustVector( b2Vec2 thrust )
	{
		mThrustVector = 0.001 * thrust;
		// velocity muss durch 1000 geteilt werden, da pro millisekunde
	}

	void EngineExhaustNode::setBaseVelocity( b2Vec2 bvel )
	{
		mBaseVelocity = 0.001 * bvel;
	}

	void EngineExhaustNode::setDamage( float damage )
	{
		/// \todo optimize this code!
		for(auto fire : mFireEmitters )
		{
			if( damage < 0.25 )
			{
				fire->setMaterialTexture(0, SceneManager->getVideoDriver()->getTexture("smoke.png"));
				fire->setMaterialType( EMT_TRANSPARENT_ALPHA_CHANNEL );
			}

			// if repaired, reset particle system
			if( damage > 0.25 && mDamageFactor < 0.25)
			{
				fire->setMaterialTexture(0, mFireTexture);
				fire->setMaterialType(/*EMT_TRANSPARENT_VERTEX_ALPHA*/EMT_TRANSPARENT_ADD_COLOR);
			}
		}

		mDamageFactor = damage;
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

	void EngineExhaustNode::OnRegisterSceneNode()
	{
		ISceneNode::OnRegisterSceneNode();
	}
}

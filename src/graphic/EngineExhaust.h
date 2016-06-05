#ifndef ENGINE_FIRE_NODE_H
#define ENGINE_FIRE_NODE_H

#include <irrlicht/ISceneNode.h>
#include <irrlicht/IParticleSystemSceneNode.h>
#include <vector>
#include <Box2D/Common/b2Math.h>

namespace irr
{
	namespace scene
	{
		class IParticleFadeOutAffector;
	}
}

namespace gfx
{
	using namespace irr;
	using namespace scene;
	using namespace core;

	class EngineExhaustNode: public ISceneNode
	{
		public:
			EngineExhaustNode(ISceneNode* parent, ISceneManager *mgr, s32 id,
								float radius, float psize, bool light = false);
			virtual ~EngineExhaustNode();

			void OnRegisterSceneNode() override;
			void OnAnimate(u32 timeMs) override;
			void render() override;

			const core::aabbox3d<f32>& getBoundingBox() const override;
			
			// setting basic properties
			void setParticleSize( f32 size );
			void setParticleLifetime( u32 lifetime );
			void setParticleCount( u32 max_particles );
			
			// setting dynamic state
			/// this is the velocity of the exhaust relative to the ship.
			void setExhaustVelocity( core::vector3df velocity );
			/// this is the velocity with which the ship moves itself.
			void setShipVelocity( core::vector3df velocity );

			void setIntensity( float it );

			void setOverrideTexture( video::ITexture* texture, video::E_MATERIAL_TYPE material );

			// add engine nozzle
			void addNozzle( irr::core::vector3df offset );

		private:
			// configuration
			f32 mParticleSize;		// particle size
			u32 mParticleLifetime = 800;
			u32 mMaxParticles = 100;
			
			// dynamic state
			irr::core::vector3df mExhaustVelocity;
			irr::core::vector3df mShipVelocity;
			
			// working parts
			std::vector<IParticleSystemSceneNode*> mFireEmitters;
			video::ITexture* mFireTexture;

			IParticleFadeOutAffector* mFadeOutAffector;
			IParticleAffector* mScaleAffector;

			float mRadius;				// emitter radius
	};
}


#endif

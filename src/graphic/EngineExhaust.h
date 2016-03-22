#ifndef ENGINE_FIRE_NODE_H
#define ENGINE_FIRE_NODE_H

#include <irrlicht/ISceneNode.h>
#include <irrlicht/IParticleSystemSceneNode.h>
#include <vector>
#include <Box2D/Common/b2Math.h>

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
			~EngineExhaustNode();

			void OnRegisterSceneNode();
			void OnAnimate(u32 timeMs);
			void render();

			const core::aabbox3d<f32>& getBoundingBox() const {
				//! \todo BoundingBox festlegen
			};

			void setIntensity( float it );
			void setThrustVector( b2Vec2 vec );
			void setBaseVelocity( b2Vec2 bvel );
			void setDamage( float damage );

			void setOverrideTexture( video::ITexture* texture, video::E_MATERIAL_TYPE material );

			// add engine nozzle
			void addNozzle( irr::core::vector3df offset );

		private:
			std::vector<IParticleSystemSceneNode*> mFireEmitters;
			video::ITexture* mFireTexture;

			IParticleAffector* mFadeOutAffector;
			IParticleAffector* mScaleAffector;

			float mRadius;				// emitter radius
			float mParticleSize;		// particle size

			float mIntensity;
			float mDamageFactor;		// damage status to determine when to use smoke particles
			b2Vec2 mThrustVector;
			b2Vec2 mBaseVelocity;
	};
}


#endif

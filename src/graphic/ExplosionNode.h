#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include <irrlicht/ISceneNode.h>

namespace irr
{
	namespace scene
	{
		class IParticleSystemSceneNode;
		class ILightSceneNode;
		class IParticleEmitter;
	}
}

namespace gfx
{
	using namespace irr;
	using namespace scene;
	using namespace core;

	class ExplosionNode: public ISceneNode
	{
		public:
			ExplosionNode(ISceneNode* parent, ISceneManager *mgr, s32 id, float intensity);
			~ExplosionNode();

			void OnRegisterSceneNode();
			void OnAnimate(u32 timeMs);
			void render();

			const core::aabbox3d<f32>& getBoundingBox() const {
				//! \todo BoundingBox festlegen
			};


		private:
			IParticleSystemSceneNode* mFire;
			ILightSceneNode* mLight;
			IParticleEmitter* mEmitter;
			int mGenerationTimer;
			int mLastTime;
			float mIntensity;
	};
}

#endif // EXPLOSION_H_INCLUDED

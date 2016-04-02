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

	namespace video
	{
		class ITexture;
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

			ExplosionNode(ISceneNode* parent, ISceneManager *mgr, s32 id,
							f32 intensity, video::ITexture* fire_tex);
			virtual ~ExplosionNode();

			void OnRegisterSceneNode() override;
			void OnAnimate(u32 timeMs) override;
			void render() override;

			const core::aabbox3d<f32>& getBoundingBox() const override;

			// data getters
			f32 getIntensity() const;
			video::ITexture* getTexture() const;

		private:
			IParticleSystemSceneNode* mFire;
			ILightSceneNode* mLight;
			IParticleEmitter* mEmitter;
			int mGenerationTimer;
			int mLastTime;

			f32 mIntensity;

			// textures
			video::ITexture* mFireTexture;

	};
}

#endif // EXPLOSION_H_INCLUDED

#ifndef TRACK_OBJECT_CAMERA_H_INCLUDED
#define TRACK_OBJECT_CAMERA_H_INCLUDED

#include <irrlicht/ISceneNodeAnimator.h>

namespace gfx
{
	using namespace irr;
	using namespace scene;
	using namespace core;

	//! \todo das muss auch mit nicht Kamera Szenenknoten gehen!
	class TrackObjectAnimator : public ISceneNodeAnimator
	{
		public:
			TrackObjectAnimator(const ISceneNode* objToTrack, double smoothness);
			virtual ~TrackObjectAnimator();

			void animateNode(ISceneNode* node, u32 timeMs) override;
			ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager = 0) override;
			bool hasFinished() const override;

			void setSmoothness(double smth);
			double getSmoothness() const;

		private:
			const ISceneNode* target;

			double smoothness;
			u32 lastTime;
	};

}



#endif

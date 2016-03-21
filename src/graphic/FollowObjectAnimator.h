#ifndef FOLLOW_OBJECT_CAMERA_H_INCLUDED
#define FOLLOW_OBJECT_CAMERA_H_INCLUDED

#include <irrlicht/ISceneNodeAnimator.h>

namespace gfx
{
	using namespace irr;
	using namespace scene;
	using namespace core;

	//! \todo Coding-Style and comments
	class FollowObjectAnimator : public ISceneNodeAnimator
	{
		public:
			FollowObjectAnimator(const ISceneNode* objToFollow, double distance, double smoothness,
					 double maxSpeed, vector3df offset);
			virtual ~FollowObjectAnimator();

			// implement animator interface
			void animateNode(ISceneNode* node, u32 timeMs) override;
			ISceneNodeAnimator* createClone(ISceneNode* node, ISceneManager* newManager = 0) override;
			bool hasFinished() const override;

			void setTarget(const ISceneNode* target);
			const ISceneNode* getTarget() const;

			void setSpeed(double sp);
			double getSpeed() const;

			void setSmoothness(double smth);
			double getSmoothness() const;

			void setDistance(double dis);
			double getDistance() const;

			void setOffset(vector3df of);
			vector3df getOffset() const;

		private:
			const ISceneNode* target;

			double mSpeed;
			double smoothness;
			double distance;
			vector3df offset;

			u32 lastTime;
	};

}

#endif

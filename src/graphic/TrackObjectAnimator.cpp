#include "TrackObjectAnimator.h"
#include <irrlicht/ICameraSceneNode.h>

namespace gfx
{

	TrackObjectAnimator::TrackObjectAnimator(const ISceneNode* objToTrack,
				double smooth) :
		target(objToTrack),
		smoothness(smooth),
		lastTime(0)
	{
		target->grab();
	}

	TrackObjectAnimator::~TrackObjectAnimator()
	{
	 	target->drop();
	}

	bool TrackObjectAnimator::hasFinished() const
	{
		return false;
	}

	void TrackObjectAnimator::animateNode(ISceneNode* node, u32 timeMs)
	{
		if (!node || node->getType() != ESNT_CAMERA)
			return;

		// this cast is save because node->getType is ESNT_CAMERA
		ICameraSceneNode* camera = reinterpret_cast<ICameraSceneNode*>(node);
		if(lastTime && camera)
		{
			double dt = smoothness * (timeMs - lastTime);
			double fak = pow(0.5, dt);

			auto& targetp = target->getPosition();

			camera->setTarget(fak * camera->getTarget() + (1-fak)*targetp);
		}
		lastTime = timeMs;
	}

	ISceneNodeAnimator* TrackObjectAnimator::createClone(ISceneNode* node, ISceneManager* newManager)
	{
		return new TrackObjectAnimator(target, smoothness);
	}

	void TrackObjectAnimator::setSmoothness(double smth)
	{
		smoothness = smth;
	}

	double TrackObjectAnimator::getSmoothness() const
	{
		return smoothness;
	}
}

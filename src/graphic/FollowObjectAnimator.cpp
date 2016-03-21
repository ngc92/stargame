#include "FollowObjectAnimator.h"
#include <irrlicht/ISceneNode.h>
#include <iostream>

namespace gfx
{
	FollowObjectAnimator::FollowObjectAnimator(const ISceneNode* objToFollow,
				double dis, double smooth, double maxSpeed, vector3df off) :
					target(objToFollow),
					mSpeed(maxSpeed),
					smoothness(smooth * 1000.0),
					distance(dis),
					offset(off),
					lastTime(0)
	{
		target->grab();
	}

	FollowObjectAnimator::~FollowObjectAnimator()
	{
		target->drop();
	}

	void FollowObjectAnimator::animateNode(ISceneNode* node, u32 timeMs)
	{
		if(lastTime)
		{
			double dt = (timeMs - lastTime) / 1000.0;
			double fak = pow(0.5, smoothness * dt);

			vector3df tpos = target->getPosition();
			vector3df ltarg = target->getRotation().rotationToDirection(core::vector3df(0, 0, distance));
			vector3df targetpos = ltarg + tpos + offset;

			vector3df vel = (fak-1) * node->getPosition() + (1-fak)*targetpos ;

			if(vel.getLengthSQ() > mSpeed * mSpeed * dt * dt)
			{
				vel.setLength(mSpeed * dt);
			}

			node->setPosition(node->getPosition() + vel );
		}
		lastTime = timeMs;
	}

	ISceneNodeAnimator* FollowObjectAnimator::createClone(ISceneNode* node, ISceneManager* newManager)
	{
		return new FollowObjectAnimator(target, mSpeed, smoothness, distance, offset);
	}

	bool FollowObjectAnimator::hasFinished() const
	{
		return false;
	}

	void FollowObjectAnimator::setTarget(const ISceneNode* t)
	{
		target = t;
	}

	const ISceneNode* FollowObjectAnimator::getTarget() const
	{
		return target;
	}

	void FollowObjectAnimator::setSpeed(double sp)
	{
		mSpeed = sp;
	}

	double FollowObjectAnimator::getSpeed() const
	{
		return mSpeed;
	}

	void FollowObjectAnimator::setSmoothness(double smth)
	{
		smoothness = smth;
	}
	double FollowObjectAnimator::getSmoothness() const
	{
		return smoothness;
	}

	void FollowObjectAnimator::setDistance(double dis)
	{
		distance = dis;
	}

	double FollowObjectAnimator::getDistance() const
	{
		return distance;
	}

	void FollowObjectAnimator::setOffset(vector3df of)
	{
		offset = of;
	}

	vector3df FollowObjectAnimator::getOffset() const
	{
		return offset;
	}

}

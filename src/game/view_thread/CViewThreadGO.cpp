#include "CViewThreadGO.h"
#include "property/CProperty.h"
#include "property/CPropertyObject.h"
#include <boost/algorithm/string/predicate.hpp>
#include <iostream>
#include "property/io.h"

namespace game
{
namespace view_thread
{
	CViewThreadGameObject::CViewThreadGameObject(uint64_t id) :
		CPropertyObject( "" ), mID(id)
	{
	}

	CViewThreadGameObject::~CViewThreadGameObject()
	{
		mRemoveListeners.notify();
	}


	/// gets the current position of the game object
	b2Vec2 CViewThreadGameObject::position() const
	{
		return mPosition;
	}

	float CViewThreadGameObject::angle() const
	{
		return mAngle;
	}

	b2Vec2 CViewThreadGameObject::velocity() const
	{
		return mVelocity;
	}

	float CViewThreadGameObject::angular_velocity() const
	{
		return mAngularVelocity;
	}

	uint64_t CViewThreadGameObject::id() const
	{
		return mID;
	}

	ListenerRef CViewThreadGameObject::addStepListener(std::function<void()> lst)
	{
		return mStepListeners.addListener( std::move(lst) );
	}

	ListenerRef CViewThreadGameObject::addRemoveListener( std::function<void()> lst )
	{
		return mRemoveListeners.addListener( std::move(lst) );
	}

	ListenerRef CViewThreadGameObject::addImpactListener(std::function<void(IGameObjectView&, const ImpactInfo&)>lst)
	{
		/// \todo figure out what to do with impact listeners
	}

	/// checks whether the referenced object is still alive.
	bool CViewThreadGameObject::isAlive() const
	{
		return mIsAlive;
	}
}
}

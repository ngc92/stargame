#include "CGameObject.h"
#include <cassert>
#include "Box2D/Box2D.h"
#include "property/IProperty.h"
#include "IGameObjectModule.h"

namespace game
{
	CGameObject::CGameObject(b2Body* b, long id) :
		 CPropertyObject("object"),
		 mBody(b),
		 mIsAlive(true),
		 mID(id)
	{
		assert(mBody);
		mBody->SetUserData(this);
	}

	CGameObject::~CGameObject()
	{
		if(mBody) mBody->GetWorld()->DestroyBody(mBody);
	}

	void CGameObject::remove()
	{
		mIsAlive = false;
		mBody->GetWorld()->DestroyBody(mBody);
		mBody = nullptr;

		mRemoveListeners.notify();
	}

	void CGameObject::onInit(IGameWorld& world)
	{
		for(auto& module : mModules)
			module->onInit(*this, world);
	}

	void CGameObject::onStep(const IGameWorld& world, WorldActionQueue& push_action)
	{
		mStepListeners.notify();

		for(auto& module : mModules)
		{
			// check that the object is still alive before each call,
			// in case one of the modules decides to kill the object
			// in this step.
			if(isAlive())
				module->onStep(*this, world, push_action);
		}

		// update property listeners
		notifyAll();
	}

	void CGameObject::onImpact(IGameObject& other, const ImpactInfo& info)
	{
		for(auto& module : mModules)
			module->onImpact(*this, other, info);

		mImpactListeners.notify(other, info);
	}

	void CGameObject::dealDamage( const Damage& damage, const b2Vec2& pos, const b2Vec2& dir )
	{
		for(auto& module : mModules)
			module->onDamage(*this, damage, pos, dir);
	}

	/// collision filter data. This is currently very specialised, so maybe a more general
	/// interface would be nice. However, we need to ensure that this does not cost performance for objects
	/// that do not require special collision handling.
	/// Right now, we can set one specific body with which this object shall not collide.
	const b2Body* CGameObject::ignoreCollisionTarget() const
	{
		return mIgnoreBody;
	}

	/// sets the body which shall be ignored upon collision checks
	void CGameObject::setIgnoreCollisionTarget( const b2Body* ignore )
	{
		mIgnoreBody = ignore;
	}

	b2Vec2 CGameObject::position() const
	{
		return mBody->GetPosition();
	}

	float CGameObject::angle() const
	{
		return std::fmod(mBody->GetAngle(), 2 * irr::core::PI);
	}

	b2Vec2 CGameObject::velocity() const
	{
		return mBody->GetLinearVelocity();
	}

	float CGameObject::angular_velocity() const
	{
		return mBody->GetAngularVelocity();
	}

	ListenerRef CGameObject::addStepListener( std::function<void()> lst )
	{
		return mStepListeners.addListener( std::move(lst) );
	}

	ListenerRef CGameObject::addImpactListener( std::function<void(IGameObjectView&, const ImpactInfo&)> lst )
	{
		return mImpactListeners.addListener( std::move(lst) );
	}

	ListenerRef CGameObject::addRemoveListener( std::function<void()> lst )
	{
		return mRemoveListeners.addListener( std::move(lst) );
	}


	long CGameObject::id() const
	{
		return mID;
	}

	const b2Body* CGameObject::body() const
	{
		return mBody;
	}

	b2Body* CGameObject::getBody()
	{
		return mBody;
	}

	bool CGameObject::isAlive() const
	{
		return mIsAlive;
	}

	void CGameObject::addModule( std::shared_ptr<IGameObjectModule> module )
	{
		mModules.push_back( std::move(module) );
		addChild( mModules.back() );
	}
}

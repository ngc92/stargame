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
	}

	void CGameObject::onInit()
	{
		for(auto& module : mModules)
			module->onInit(*this);
	}

	void CGameObject::onStep()
	{
		mStepListeners.notify();

		for(auto& module : mModules)
			module->onStep(*this);

		// update property listeners
		notifyAll();
	}

	void CGameObject::onImpact(IGameObject* other, const ImpactInfo& info)
	{
		for(auto& module : mModules)
			module->onImpact(*this, other, info);

		mImpactListeners.notify(other, info);
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

	ListenerRef CGameObject::addImpactListener( std::function<void(IGameObjectView*, const ImpactInfo&)> lst )
	{
		return mImpactListeners.addListener( std::move(lst) );
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

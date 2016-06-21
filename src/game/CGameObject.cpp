#include "CGameObject.h"
#include <cassert>
#include "property/IProperty.h"
#include "IGameObjectModule.h"

namespace game
{
	CGameObject::CGameObject(uint64_t id, b2Body* b, std::string name) :
		 CPropertyObject( std::move(name) ),
		 mBody(b),
		 mIsAlive(true),
		 mID(id)
	{
		assert(mBody);
		mBody.setUserPointer(this);
	}

	CGameObject::~CGameObject()
	{
		mBody.destroy();
	}

	void CGameObject::remove()
	{
		mIsAlive = false;
		mBody.destroy();

		mRemoveListeners.notify();
	}

	void CGameObject::onInit(IGameWorld& world)
	{
		for(auto& module : mModules)
			module->onInit(*this, world);
	}

	void CGameObject::onStep(const IGameWorld& world, WorldActionQueue& push_action)
	{
		// step listeners and modules
		/// \todo this should happen after the modules, I think?
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
		return mBody.position();
	}

	float CGameObject::angle() const
	{
		return std::fmod(mBody.angle(), 2 * irr::core::PI);
	}

	b2Vec2 CGameObject::velocity() const
	{
		return mBody.velocity();
	}

	float CGameObject::angular_velocity() const
	{
		return mBody.angular_velocity();
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


	uint64_t CGameObject::id() const
	{
		return mID;
	}

	const Body& CGameObject::body() const
	{
		return mBody;
	}

	Body& CGameObject::getBody()
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

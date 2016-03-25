#include "GameObject.h"
#include <cassert>
#include "Box2D/Box2D.h"

namespace game
{
	GameObject::GameObject(b2Body* b, long id) :
		 mBody(b),
		 mIsAlive(true),
		 mID(id)
	{
		assert(mBody);
		mBody->SetUserData(this);
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::remove()
	{
		mIsAlive = false;
	}

	void GameObject::onStep()
	{
		mStepListeners.notify();
	}

	void GameObject::onImpact(GameObject* other, const ImpactInfo& info)
	{
		mImpactListeners.notify(other, info);
	}

	void GameObject::destroyObject()
	{
		assert(!mIsAlive);
		mBody->GetWorld()->DestroyBody(mBody);
		mBody = nullptr;
	}

	// setter
	void GameObject::setPosition(const b2Vec2& np)
	{
		mBody->SetTransform( np, mBody->GetAngle() );
	}

	void GameObject::setRotation(float rot)
	{
		mBody->SetTransform( mBody->GetPosition(), rot );
	}

	void GameObject::setVelocity(const b2Vec2& vel)
	{
		b2Vec2 targetVelocity = vel;
		// we don't set velocity directly, instead we apply an impulse
		b2Vec2 dv = targetVelocity - mBody->GetLinearVelocity();
		mBody->ApplyLinearImpulse(mBody->GetMass() * dv, mBody->GetWorldCenter());
	}

	// getter
	b2Vec2 GameObject::getPosition() const
	{
		return mBody->GetPosition();
	}

	float GameObject::getRotation() const
	{
		return std::fmod(mBody->GetAngle(), 2 * irr::core::PI);
	}

	b2Vec2 GameObject::getVelocity() const
	{
		return mBody->GetLinearVelocity();
	}

	float GameObject::getAngularVelocity() const
	{
		return mBody->GetAngularVelocity();
	}


	b2Vec2 GameObject::getVelocityInLocalPoint(const b2Vec2& p)
	{
		return mBody->GetLinearVelocityFromLocalPoint(p);
	}

	b2Vec2 GameObject::getLocalPoint( b2Vec2 worldPoint ) const
	{
		return mBody->GetLocalPoint( worldPoint );
	}

	b2Vec2 GameObject::getWorldPoint( b2Vec2 localPoint ) const
	{
		return mBody->GetWorldPoint( localPoint );
	}

	b2Vec2 GameObject::getLocalVector( b2Vec2 worldVector ) const
	{
		return mBody->GetLocalVector( worldVector );
	}

	b2Vec2 GameObject::getWorldVector( b2Vec2 localVector ) const
	{
		return mBody->GetWorldVector( localVector );
	}

	float GameObject::rayCast( b2Vec2 p1, b2Vec2 p2 ) const
	{
		float fraction = -1;
		b2RayCastInput rci;
		rci.maxFraction = 1.0;
		rci.p1 = p1;
		rci.p2 = p2;

		for( auto f = mBody->GetFixtureList(); f; f = f->GetNext() )
		{
			b2RayCastOutput rco;
			if(f->RayCast( &rco, rci, 0 ))
			{
				rci.maxFraction = rco.fraction;
				fraction = rco.fraction;
			}
		}

		return fraction;
	}

	bool GameObject::testPoint( b2Vec2 point ) const
	{
		for( auto f = mBody->GetFixtureList(); f; f = f->GetNext() )
			if(f->TestPoint( point ))
				return true;

		return false;
	}

	void GameObject::addPropertyObject( const std::string& name, IPropertyObject* pob )
	{
		auto res = mPropertySubobjects.emplace(name, pob);
		assert(res.second);
	}
}

#include "ContactListener.h"
#include "game/IGameObject.h"
#include <Box2D/Box2D.h>

namespace game
{

	ContactListener::ContactListener()
	{
	}

	ContactListener::~ContactListener()
	{
	}


	struct ContactListener::Contact
	{
		std::weak_ptr<IGameObjectView> A;
		std::weak_ptr<IGameObjectView> B;
		b2Vec2 position;
		b2Vec2 normal;
		float impulse;
		b2Fixture* fixA;
		b2Fixture* fixB;
	};

	void ContactListener::BeginContact(b2Contact* contact)
	{
	}

	void ContactListener::EndContact(b2Contact* contact)
	{

	}

	void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* old)
	{
	}

	void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
		// get pointer to GameObjects
		IGameObject* ob1 = (IGameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
		IGameObject* ob2 = (IGameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

		float imp = impulse->normalImpulses[0];

		if(ob1 && ob2 && imp > 0 && ob1->isAlive() && ob2->isAlive())
		{
			b2WorldManifold wm;
			contact->GetWorldManifold(&wm);
			mResponseQueue.push_back(Contact{ob1->shared_from_this(), ob2->shared_from_this(),
										wm.points[0], wm.normal, imp,
										contact->GetFixtureA(), contact->GetFixtureB()});
		}
	}

	bool ContactListener::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
	{
		b2Body* bodyA = fixtureA->GetBody();
		b2Body* bodyB = fixtureB->GetBody();
		const IGameObject* ob1 = (IGameObject*)bodyA->GetUserData();
		const IGameObject* ob2 = (IGameObject*)bodyB->GetUserData();

		if(ob1->ignoreCollisionTarget() == bodyB || ob2->ignoreCollisionTarget() == bodyA)
			return false;

		return true;
	}

	void ContactListener::triggerEvents()
	{
		for(auto& c : mResponseQueue)
		{
			auto A = std::dynamic_pointer_cast<IGameObject>(c.A.lock());
			auto B = std::dynamic_pointer_cast<IGameObject>(c.B.lock());

			if(A && B && A->isAlive() && B->isAlive())
			{
				ImpactInfo info;
				info.position = c.position;
				info.impulse = c.impulse;

				info.normal = c.normal;
				info.fixture = c.fixA;

				A->onImpact(*B, info);

				info.normal = -c.normal;
				info.fixture = c.fixB;
				B->onImpact(*A, info);
			}
		}

		mResponseQueue.clear();
	}

}

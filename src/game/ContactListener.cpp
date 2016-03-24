#include "ContactListener.h"
#include "GameObject.h"
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
		std::weak_ptr<GameObject> A;
		std::weak_ptr<GameObject> B;
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
		GameObject* ob1 = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData();
		GameObject* ob2 = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData();

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

	void ContactListener::triggerEvents()
	{
		for(auto& c : mResponseQueue)
		{
			auto A = c.A.lock();
			auto B = c.A.lock();

			if(A->isAlive() && B->isAlive())
			{
				ImpactInfo info;
				info.position = c.position;
				info.impulse = c.impulse;

				info.normal = c.normal;
				info.fixture = c.fixA;

				A->onImpact(B.get(), info);

				info.normal = -c.normal;
				info.fixture = c.fixB;
				B->onImpact(A.get(), info);
			}

		}
	}

}

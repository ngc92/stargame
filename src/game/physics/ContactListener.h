#ifndef CONTACTLISTENER_H_INCLUDED
#define CONTACTLISTENER_H_INCLUDED

#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <vector>

namespace game
{

	/*! \class ContactListener
		\brief Listener for the Box2D world.
		\details This class collects all contact events of the physics
				world, and relays them to the corresponding game objects.
				The events in the GameObjects are triggered only after
				Box2D has finished its update phase, so it is safe to
				change b2Body's in the callback.
				This class also implements a contact filter interface to
				determine whether two fixtures are allowed to collide!
	*/
	class ContactListener : public b2ContactListener, public b2ContactFilter
	{
	public:
		ContactListener();
		~ContactListener();
		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;

		void PreSolve(b2Contact* contact, const b2Manifold* old) override;
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
		
		/// Return true if contact calculations should be performed between these two shapes.
		/// @warning for performance reasons this is only called when the AABBs begin to overlap.
		bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);

		/// triggers on hit events based on the collected callbacks
		void triggerEvents();

	private:
		struct Contact;
		std::vector<Contact> mResponseQueue;
	};

}

#endif // CONTACTLISTENER_H_INCLUDED

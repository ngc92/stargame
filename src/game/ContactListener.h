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
	*/
	class ContactListener : public b2ContactListener
	{
	public:
		~ContactListener();
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;

		virtual void PreSolve(b2Contact* contact, const b2Manifold* old) override;
		virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

		/// triggers on hit events based on the collected callbacks
		void triggerEvents();

	private:
		struct Contact;
		std::vector<Contact> mResponseQueue;
	};

}

#endif // CONTACTLISTENER_H_INCLUDED

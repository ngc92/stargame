#ifndef CVIEWTHREADGAMEOBJECTVIEW
#define CVIEWTHREADGAMEOBJECTVIEW

#include "game/IGameObject.h"
#include <functional>
#include <vector>

#include "property/CPropertyObject.h"
#include "listener/listenerlist.h"

namespace property
{
	class IProperty;
}

namespace game
{
namespace view_thread
{
    /** \class CViewThreadGameObject
		\brief Game Object view that acts from within another thread.
     */
	class CViewThreadGameObject : public IGameObject, public virtual property::CPropertyObject
	{
	public:
		void onInit(IGameWorld& world) { }

		void onStep(const IGameWorld& world, WorldActionQueue& push_action) { }

		void onImpact(IGameObject& other, const ImpactInfo& info) { };

		/// call this function to deal damage to this game object.
		void dealDamage( const Damage& damage, const b2Vec2& pos, const b2Vec2& dir ) { };

		/// get a pointer to the internal body, if any
		const Body& body() const  { };

		/// get a pointer to the internal body, if any
		Body& getBody() { };

		/// marks this body for deletion.
		virtual void remove() {};

		/// collision filter data. This is currently very specialised, so maybe a more general
		/// interface would be nice. However, we need to ensure that this does not cost performance for objects
		/// that do not require special collision handling.
		/// Right now, we can set one specific body with which this object shall not collide.
		virtual const b2Body* ignoreCollisionTarget() const {};

		/// sets the body which shall be ignored upon collision checks
		virtual void setIgnoreCollisionTarget( const b2Body* ignore ) {};

		CViewThreadGameObject( uint64_t id );

		~CViewThreadGameObject();

		/// gets the current position of the game object
		b2Vec2 position() const final;
		/// gets the current rotation angle.
		float angle() const final;
		/// gets the current velocity.
		b2Vec2 velocity() const final;
		/// gets the current angular velocity.
		float angular_velocity() const final;
		/// gets an ID for object identification.
		uint64_t id() const final;

		/// adds a listener that is called every step for this game object.
		/// \note this listener is executed whenever the view thread steps, not when the game thread steps.
		ListenerRef addStepListener( std::function<void()> lst ) final;

		/// adds a listener that is called when this object is hit by another game object.
		/// \warning The impact listener is executed within the game thread! It thus cannot
		///			safely access data from the view thread.
		ListenerRef addImpactListener( std::function<void(IGameObjectView&, const ImpactInfo&)> lst ) final;

		/// adds a listener that is called when the object is removed.
		ListenerRef addRemoveListener( std::function<void()> lst ) final;

		/// checks whether the referenced object is still alive.
		bool isAlive() const final;

		// modules
		/// adds a module to this game object.
		virtual void addModule( std::shared_ptr<IGameObjectModule> ) {}

		virtual module_vec& getModules() {};

	private:
		const uint64_t mID;			//!< object ID, unchangeable.
		b2Vec2 mPosition;		//!< position at last update.
		b2Vec2 mVelocity;		//!< velocity at last update.
		float mAngle;			//!< angle at last update.
		float mAngularVelocity;	//!< angular velocity at last update.

		bool mIsAlive = true;						//!< is this object still considered alive?

		ListenerList<> mStepListeners;
		ListenerList<> mRemoveListeners;
	};
}
}

#endif // CVIEWTHREADGAMEOBJECTVIEW

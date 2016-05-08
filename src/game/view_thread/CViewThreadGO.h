#ifndef CVIEWTHREADGAMEOBJECTVIEW
#define CVIEWTHREADGAMEOBJECTVIEW

#include "IViewThreadGO.h"
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
	class CViewThreadGameObject : public IViewThreadGameObject, public virtual property::CPropertyObject
	{
	public:

		CViewThreadGameObject(IGameObjectView& object);

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
		long id() const final;

		/// adds a listener that is called every step for this game object.
		ListenerRef addStepListener( std::function<void()> lst ) final;

		/// adds a listener that is called when this object is hit by another game object.
		/// \warning The impact listener is executed within the game thread! It thus cannot
		///			safely access data from the view thread.
		ListenerRef addImpactListener( std::function<void(IGameObjectView*, const ImpactInfo&)> lst ) final;


		/*! update the thread view with the original data.
			\details This function shall only be called
				when it is save to access \p object
				without danger of race conditions, i.e.
				outside the game loop.
		*/
		void update() final;

		/*! called inside the view thread to do the update
			step of the GameObjectView. From within this
			function, it is save to manipulate data
			within the view thread, but not the game thread.

			Calls the step listener.
		*/
		void onStep() final;

		/// checks whether the referenced object is still alive.
		bool isAlive() const final;

		/*! \brief Allows setting properties from view thread.
			\details This function caches assignments to properties
					from the view thread, which then are performed
					inside the game thread.
		*/
		void setProperty( const std::string& path, const property::data_t& value) final;

	private:
		const long mID;			//!< object ID, unchangeable.
		b2Vec2 mPosition;		//!< position at last update.
		b2Vec2 mVelocity;		//!< velocity at last update.
		float mAngle;			//!< angle at last update.
		float mAngularVelocity;	//!< angular velocity at last update.

		std::weak_ptr<IGameObjectView> mOriginal;	//!< reference to the original game object.

		// threading stuff
		using delayed_fun = std::function<void(IGameObjectView&)>;
		std::vector<delayed_fun> mDelayedActions;

		/// adds a delayed action to the update queue.
		/// \warning this function is not mutex protected and as such should only be called
		/// from the game simulation thread.
		void addDelayedAction( delayed_fun f );

		ListenerList<> mStepListeners;

		/// updates a property of the original game object
		static void updateProperty(IGameObjectView& object, const std::string& path, const property::data_t& value);
	};
}
}

#endif // CVIEWTHREADGAMEOBJECTVIEW

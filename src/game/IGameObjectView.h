#ifndef IGAMEOBJECTVIEW_H_INCLUDED
#define IGAMEOBJECTVIEW_H_INCLUDED

#include "util.h"
#include "listener/listenerlist.h"
#include "property/IPropertyObject.h"

class b2Fixture;

namespace game
{
	enum class ObjectCategory : int
	{
		SPACESHIP, 
		BULLET
	};
	
	
	/*! \struct ImpactInfo
		\brief Data relating to impact
		\details This struct contains the necessary data to process
				a physics collision.
				Listeners:
				 * step listener: called for every game step, or for every view step, depending on whether
							the view object belongs to the game thread or to a view thread [It does not make
							sense for the view thread to call in every original step by default].
	*/
	struct ImpactInfo
	{
		b2Fixture* 	fixture; 	//!< The fixture that was hit
		b2Vec2 		normal;		//!< The (outwards) normal at the point of impact.
		b2Vec2		position;	//!< The position of impact.
		float		impulse;	//!< The transferred normal impulse ("strength" of the impact)
	};


	/*! \class IGameObjectView
		\brief Observer class for Game Objects.
		\details This class defines a read only interface to Game Objects, that allows
				setting listeners. A GameObject constitutes a property object, so this
				view is virtually derived from the property view.
	*/
	class IGameObjectView : noncopyable, public virtual property::IPropertyObjectView,
							public std::enable_shared_from_this<IGameObjectView>
	{
	public:
		virtual ~IGameObjectView() = default;

		/// gets the current position of the game object
		virtual b2Vec2 position() const = 0;
		/// gets the current rotation angle.
		virtual float angle() const = 0;
		/// gets the current velocity.
		virtual b2Vec2 velocity() const = 0;
		/// gets the current angular velocity.
		virtual float angular_velocity() const = 0;
		/// gets an ID for object identification.
		virtual uint64_t id() const = 0;
		/// gets the object type. This is the type that
		/// was used to get the spawn data for the object.
		virtual const std::string& type() const = 0;
		/// the category of this object. 
		virtual ObjectCategory category() const = 0;

		/// return whether the game object is considered to be alive, or marked for deletion.
		virtual bool isAlive() const = 0;

		/// adds a listener that is called every step for this game object.
		virtual ListenerRef addStepListener( std::function<void()> lst ) = 0;
		/// adds a listener that is called when the object is removed
		virtual ListenerRef addRemoveListener( std::function<void()> lst ) = 0;
		/// adds a listener that is called when this object is hit by another game object.
		virtual ListenerRef addImpactListener( std::function<void(IGameObjectView&, const ImpactInfo&)> lst ) = 0;
	};
}

#endif // IGAMEOBJECTVIEW_H_INCLUDED

#include "CViewThreadGO.h"
#include "property/CProperty.h"
#include "property/CPropertyObject.h"
#include <boost/algorithm/string/predicate.hpp>

namespace
{
	using namespace property;
	using clistener = std::function<void(const IPropertyView&)>;
	using listener_factory = std::function<clistener(IProperty& target)>;

	// helper function to copy properties
	void copyProperties(CPropertyObject& target, const IPropertyObjectView& source,
						const listener_factory& lfac)
	{
		/// \todo add listeners for adding and removing properties, and child objects.
		source.forallProperties([&](IPropertyView& view) mutable
		{
			auto newprop = CProperty::create( view.name(), &target, view.value() );
			// set a change listener for the original property
			/// \todo not like this! not thread-save!
			view.addListener( lfac(*newprop) );
		}, false);

		// copy all children
		source.forallChildren([&](const IPropertyObjectView& view) mutable
		{
			auto child = std::make_shared<CPropertyObject>( view.name() );
			target.addChild( child );
			copyProperties(*child, view, lfac);
		});
	}
}

namespace game
{
namespace view_thread
{
	CViewThreadGameObject::CViewThreadGameObject(IGameObjectView& object) :
		CPropertyObject( object.name() ),
		mID( object.id() ),
		mPosition( object.position() ),
		mVelocity( object.velocity() ),
		mAngle( object.angle() ),
		mAngularVelocity( object.angular_velocity() ),
		mOriginal( object.shared_from_this() )
	{
		listener_factory factory = [this](property::IProperty& target) mutable -> clistener
		{
			return [&](const property::IPropertyView& source)
			{
				auto update = [&](IGameObjectView&) { target = source.value(); };
				addDelayedAction( update );
			};
		};

		// copy all properties from original into here
		copyProperties(*this, object, factory);
	}

	CViewThreadGameObject::~CViewThreadGameObject()
	{

	}


	/// gets the current position of the game object
	b2Vec2 CViewThreadGameObject::position() const
	{
		return mPosition;
	}

	float CViewThreadGameObject::angle() const
	{
		return mAngle;
	}

	b2Vec2 CViewThreadGameObject::velocity() const
	{
		return mVelocity;
	}

	float CViewThreadGameObject::angular_velocity() const
	{
		return mAngularVelocity;
	}

	long CViewThreadGameObject::id() const
	{
		return mID;
	}

	ListenerRef CViewThreadGameObject::addStepListener(std::function<void()> lst)
	{
		return mStepListeners.addListener( lst );
	}

	ListenerRef CViewThreadGameObject::addImpactListener(std::function<void(IGameObjectView*, const ImpactInfo&)>lst)
	{
		// construct the promise into a shared_ptr, as we cannot move into lambda in c++11
		using promise_t = std::promise<std::shared_ptr<listener::ListenerBase>>;
		auto promise = std::make_shared<promise_t>();

		// this lambda adds the listener to the original game object and
		// sets the listener reference in the promise.
		auto setListener_f = [lst, promise](IGameObjectView& go)
		{
			auto lref = go.addImpactListener(lst);
			promise->set_value( lref.get() );
		};

		// register it for execution in the next update step, and return the future from the promise.
		mDelayedActions.push_back( setListener_f );
		return promise->get_future();
	}

	/*! update the thread view with the original data.
		\details This function shall only be called
			when it is save to access \p object
			without danger of race conditions, i.e.
			outside the game loop.
	*/
	void CViewThreadGameObject::update()
	{
		auto locked = mOriginal.lock();
		if(!locked)
			return;

		auto& object = *locked;

        // update local variables
        mPosition = object.position();
        mVelocity = object.velocity();
        mAngle = object.angle();
        mAngularVelocity = object.angular_velocity();

        // do all delayed stuff
        for(auto& action : mDelayedActions)
		{
			action(object);
		}

		mDelayedActions.clear();
	}

	/*! called inside the view thread to do the update
		step of the GameObjectView. From within this
		function, it is save to manipulate data
		within the view thread, but not the game thread.

		Calls the step listener.
	*/
	void CViewThreadGameObject::onStep()
	{
		mStepListeners.notify();
	}

	/// checks whether the referenced object is still alive.
	bool CViewThreadGameObject::isAlive() const
	{
		return !mOriginal.expired();
	}

	void CViewThreadGameObject::addDelayedAction( delayed_fun f )
	{
		mDelayedActions.push_back( std::move(f) );
	}

	/*! \brief Allows setting properties from view thread.
		\details This function caches assignments to properties
				from the view thread, which then are performed
				inside the game thread.
	*/
	void CViewThreadGameObject::setProperty( const std::string& path, const property::data_t& value)
	{
		mDelayedActions.push_back( [value, path](IGameObjectView& o){ updateProperty(o, path, value); } );
	}

	/// updates a property of the original game object
	void CViewThreadGameObject::updateProperty(IGameObjectView& object, const std::string& path, const property::data_t& value)
	{
		auto& property = object.getProperty(path);
		dynamic_cast<property::IProperty&>(property).assign(value);

	}
}
}

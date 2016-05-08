#ifndef IPROPERTYVIEW_H_INCLUDED
#define IPROPERTYVIEW_H_INCLUDED

#include <string>
#include <functional>
#include <boost/variant.hpp>
#include "property.h"
#include "listener/listener.h"
#include <Box2D/Common/b2Math.h>

namespace property
{
	using data_t = boost::variant<float, int, std::string, b2Vec2>;

	// forward decls
	class IPropertyView;
	class IProperty;
	class IPropertyObject;

	/*! \class IPropertyView
		\brief A property is a named value that provides a change listener.
		\details This class provides a read only interface to property values.
				It allows retrieving the current value and adding change
				listeners. As properties are usually part of a property object,
				a function owner allows to get the owner.
	*/
	class IPropertyView
	{
	public:
		using listener_t = std::function<void(IPropertyView&)>;

		/// returns the name of the property
		virtual const std::string& name() const	noexcept		= 0;
		/// gets the path (fully qualified name) of the property.
		/// implementation is found in CProperty.cpp
		std::string path() const;
		/// returns the property object that owns this property, or nullptr
		virtual const IPropertyObject* owner() const noexcept	= 0;
		/// returns the value of the property as a variant
		virtual const data_t& value() const	noexcept			= 0;

		/// adds a listener to the property that will be triggered
		/// when the value of the property changes.
		virtual ListenerRef addListener( listener_t listener ) = 0;

		// c'tor/d'tor
		IPropertyView() = default;
		IPropertyView(IPropertyView&&) = default;
		virtual ~IPropertyView() noexcept = default;
	};
}


#endif // IPROPERTYVIEW_H_INCLUDED

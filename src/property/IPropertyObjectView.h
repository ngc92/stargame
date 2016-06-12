#ifndef IPROPERTYOBJECTVIEW_H_INCLUDED
#define IPROPERTYOBJECTVIEW_H_INCLUDED

#include <functional>
#include <memory>
#include <string>
#include "property.h"
#include "listener/listener.h"

namespace property
{
	class IPropertyObject;
	class IPropertyView;

	class PropertyViewIterator;

	/*! \class IPropertyObjectView
		\brief read-only interface to a property object.
		\details Property objects model a tree, in which each node
				contains a list of properties and optionally child
				nodes which are property objects too.

				It allows listening for property changes insert and remove,
				which are automatically also registered to all child
				objects.
	*/
	class IPropertyObjectView
	{
	public:
		/// type for a listener function that gets passed a property view.
		using listener_t = std::function<void(IPropertyView&)>;

		/// virtual d'tor
		virtual ~IPropertyObjectView() noexcept = default;

		// tree interface
		// ----------------------------------------------------------------------
		/// gets a child property object of name \p name or throws.
		/// only works for direct children.
		virtual IPropertyObjectView& getChild(const std::string& name) = 0;

		/// gets a child property object (const) of name \p name or throws.
		/// only works for direct children.
		virtual const IPropertyObjectView& getChild(const std::string& name) const = 0;

		/// gets the parent property object, or nullptr if this
		/// is the root of the tree.
		virtual const IPropertyObjectView* parent() const noexcept = 0;

		/// gets the root node, or this if no parent()
		const IPropertyObjectView* root() const noexcept;

		/// gets the name of this node.
		virtual const std::string& name() const noexcept = 0;

		/// gets the path (fully qualified name) of the property object.
		std::string path() const;

		// listeners
		// ----------------------------------------------------------------------
		/// adds a listener that is called whenever a new property is added.
		virtual ListenerRef addInsertListener( listener_t listener ) = 0;

		/// adds a listener that is called whenever a property gets removed.
		virtual ListenerRef addRemoveListener( listener_t listener ) = 0;

		/// \todo change listeners for children?

		// properties
		/// gets the property that is referred to by path (i.e. this can
		/// also access properties of child objects).
		virtual IPropertyView& getProperty(const std::string& path) const = 0;

		/// check if the property that is referred to by path (i.e. this can
		/// also access properties of child objects) exists.
		virtual bool hasProperty(const std::string& path) const = 0;

		/// \todo figure out a nice way to do the iterators here. until then, use the forallProperties function
		/// \param f Function to apply
		/// \param recurse apply to all properties of subobjects as well?
		virtual void forallProperties(const std::function<void(IPropertyView&)>& f, bool recurse = true) const = 0;

		// single level iteration
		/// applies \p f to all immediate children of this property.
		virtual void forallChildren( const std::function<void(const IPropertyObjectView&)>& f ) const = 0;
	};

	inline std::string IPropertyObjectView::path() const
	{
		if(!parent())
			return name();

		return parent()->path() + "." + name();
	}

	inline const IPropertyObjectView* IPropertyObjectView::root() const noexcept
	{
		if(!parent())
			return this;
		return parent()->root();
	}
}


#endif // IPROPERTYOBJECTVIEW_H_INCLUDED

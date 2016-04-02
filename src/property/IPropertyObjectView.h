#ifndef IPROPERTYOBJECTVIEW_H_INCLUDED
#define IPROPERTYOBJECTVIEW_H_INCLUDED

#include <functional>
#include <memory>

class ListenerRef;

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

		/// gets the name of this node
		virtual const std::string& name() const noexcept = 0;

		/// gets the path (fully qualified name) of the property object.
		/// implementation is found in CPropertyObject.cpp
		std::string path() const;

		// listeners
		// ----------------------------------------------------------------------
		/// adds a listener that is called whenever a new property is added.
		virtual ListenerRef addInsertListener( listener_t listener ) = 0;

		/// adds a listener that is called whenever a property gets removed.
		virtual ListenerRef addRemoveListener( listener_t listener ) = 0;

		/// \todo change listeners for children?

		// IPropertyView interface
		/// gets the property that is referred to by path (i.e. this can
		/// also access properties of child objects).
		virtual IPropertyView& getProperty(std::string path) const = 0;
		// iterator interface
		/*/// get the property view iterator that points to
		/// the first property of this object.
		virtual objectview_iter begin() const = 0;
		/// iterator that points behind the last property of the last subobject.
		virtual objectview_iter end() const = 0;

		/// iterator to the first property of this node.
		/// This iterator will not iterate over other nodes.
		virtual objectview_iter node_begin() const = 0;
		/// end iterator corresponding to node_begin
		virtual objectview_iter node_end() const = 0;
		*/
		/// \todo figure out a nice way to do the iterators here. until then, use the forallProperties function
		virtual void forallProperties(const std::function<void(IPropertyView&)>& f) const = 0;
	};
}


#endif // IPROPERTYOBJECTVIEW_H_INCLUDED

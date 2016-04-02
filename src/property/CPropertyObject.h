#ifndef CPROPERTYOBJECT_H_INCLUDED
#define CPROPERTYOBJECT_H_INCLUDED

#include "IPropertyObject.h"
#include "util/ListenerList.h"
#include <unordered_map>

namespace property
{
	/*! \class CPropertyObject
		\brief Default implementation of a property object.
		\details Since this is going to be used to fuse the IPropertyObject
				part into other objects, it is virtually derived from IPropertyObject.
	*/
	class CPropertyObject : public virtual IPropertyObject
	{
	public:
		CPropertyObject( std::string name );
		~CPropertyObject() noexcept;

		// tree interface
		// ----------------------------------------------------------------------
		/// gets a child property object of name \p name, or throws.
		/// only works for direct children.
		IPropertyObjectView& getChild(const std::string& name) final;

		/// gets a child property object (const) of name \p name or throws.
		/// only works for direct children.
		const IPropertyObjectView& getChild(const std::string& name) const final;

		/// gets the parent property object, or nullptr if this
		/// is the root of the tree.
		const IPropertyObjectView* parent() const noexcept final;

		/// gets the name of this node
		const std::string& name() const noexcept final;

		// listeners
		// ----------------------------------------------------------------------
		/// adds a listener that is called whenever a new property is added.
		ListenerRef addInsertListener( listener_t listener ) final;

		/// adds a listener that is called whenever a property gets removed.
		ListenerRef addRemoveListener( listener_t listener ) final;

		/// \todo change listeners for children?

		// IPropertyView interface
		/// gets the property that is referred to by path (i.e. this can
		/// also access properties of child objects).
		IPropertyView& getProperty(std::string path) const final;

		// iterator interface
		/*
		/// get the property view iterator that points to
		/// the first property of this object.
		objectview_iter begin() const final;
		/// iterator that points behind the last property of the last subobject.
		objectview_iter end() const final;

		/// iterator to the first property of this node.
		/// This iterator will not iterate over other nodes.
		property_map::iterator node_begin() const final;
		/// end iterator corresponding to node_begin
		property_map::iterator node_end() const final;
		*/

		/// iterates over all properties and calls f for them.
		void forallProperties(const std::function<void(IPropertyView&)>& f) const final;


		// --------------------------------------------------------
		/// adds a property to this property objects.
		/// \pre property.owner() == this
		void addProperty(IPropertyView& property) final;
		/// removes a property from this property objects.
		/// this method does not work for removing properties of
		/// subobjects. \todo does this make sense?
		void removeProperty(const IPropertyView& property) final;

		// add/remove children
		/// adds a child property object. Sets the parent of \p child.
		/// \pre child->parent() == nullptr.
		/// \post child()->parent() == this.
		void addChild( IPropertyObject* child ) final;

		/// remove a child object that is registered here.
		/// \pre child()->parent() == this.
		/// \post child->parent() == nullptr.
		void removeChild( IPropertyObject* child) final;

		// notification
		// ---------------------------------------------------------
		/// \brief calls notifyIfChanged on all properties.
		/// \details This function triggers the change listeners for
		///			all registered properties, including those in subobjects.
		void notifyAll() final;

	private:

		void setParent(const IPropertyObject* parent) noexcept final;

		const std::string mName;
		const IPropertyObject* mParent = nullptr;

		std::unordered_map<std::string, IPropertyView*> mProperties;
		std::unordered_map<std::string, IPropertyObject*> mChildren;

		ListenerList<IPropertyView&> mInsertListeners;
		ListenerList<IPropertyView&> mRemoveListeners;
	};

}

#endif // CPROPERTYOBJECT_H_INCLUDED

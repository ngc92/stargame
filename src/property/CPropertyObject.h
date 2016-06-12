#ifndef CPROPERTYOBJECT_H_INCLUDED
#define CPROPERTYOBJECT_H_INCLUDED

#include "IPropertyObject.h"
#include "listener/listenerlist.h"
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
		IPropertyView& getProperty(const std::string& path) const final;
		
		/// check if the property that is referred to by path (i.e. this can
		/// also access properties of child objects) exists.
		bool hasProperty(const std::string& path) const final;

		/// iterates over all properties and calls f for them.
		/// \param f Function to apply
		/// \param recurse apply to all properties of subobjects as well?
		void forallProperties(const std::function<void(IPropertyView&)>& f, bool recurse=true) const final;
		
		/// applies \p f to all immediate children of this property.
		void forallChildren( const std::function<void(const IPropertyObjectView&)>& f ) const final;


		// --------------------------------------------------------
		/// adds a property to this property objects.
		/// \pre property.owner() == this
		void addProperty(std::shared_ptr<IProperty> property) final;
		/// removes a property from this property objects.
		/// this method does not work for removing properties of
		/// subobjects. \todo does this make sense?
		void removeProperty(const IPropertyView& property) final;

		// add/remove children
		/// adds a child property object. Sets the parent of \p child.
		/// \pre child->parent() == nullptr.
		/// \post child()->parent() == this.
		void addChild( std::shared_ptr<IPropertyObject> child ) final;

		/// remove a child object that is registered here.
		/// \pre child.parent() == this.
		/// \post child.parent() == nullptr.
		void removeChild( const IPropertyObject& child) final;
		
		// notification
		// ---------------------------------------------------------
		/// \brief calls notifyIfChanged on all properties.
		/// \details This function triggers the change listeners for
		///			all registered properties, including those in subobjects.
		void notifyAll() final;

	protected:
		/// gets the property that is referred to by path (i.e. this can
		/// also access properties of child objects).
		/// this version of the function returns the internal shared_ptr.
		const std::shared_ptr<IProperty>& getPropertyPtr(const std::string& path) const final;
	
	private:

		void setParent(const IPropertyObject* parent) noexcept final;

		const std::string mName;
		const IPropertyObject* mParent = nullptr;

		std::unordered_map<std::string, std::shared_ptr<IProperty>> mProperties;
		std::unordered_map<std::string, std::shared_ptr<IPropertyObject>> mChildren;

		ListenerList<IPropertyView&> mInsertListeners;
		ListenerList<IPropertyView&> mRemoveListeners;
	};

}

#endif // CPROPERTYOBJECT_H_INCLUDED

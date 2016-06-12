#ifndef IPROPERTYOBJECT_H_INCLUDED
#define IPROPERTYOBJECT_H_INCLUDED

#include <memory>
#include "IPropertyObjectView.h"

namespace property
{
	class IProperty;
	
	/*! \class IPropertyObject
		\brief Full interface of a IPropertyObjects, extends IPropertyObjectView with add/remove
		\details Allows the addition and removal of properties and property subobjects. The
				IPropertyObject does not own the properties or subobjects, and only saves weak
				pointers.
				The tree data structure is build with shared_ptr objects, i.e. child nodes are owned by their parents.
				Parent nodes are referred to by shared_ptr objects.
	*/
	class IPropertyObject : public virtual IPropertyObjectView
	{
	public:
		// delete copy, as this would mean references of weak pointers.
		// move is ok, though
		IPropertyObject() = default;
		IPropertyObject(const IPropertyObject& ) = delete;
		IPropertyObject& operator=(const IPropertyObject& ) = delete;
		IPropertyObject(IPropertyObject&&) = default;
		IPropertyObject& operator=(IPropertyObject&&) = default;

		// add/ remove properties
		// --------------------------------------------------------
		/// adds a property to this property objects.
		/// \pre property->owner() == this
		virtual void addProperty(std::shared_ptr<IProperty> property) = 0;

		/// removes a property from this property objects.
		/// this method does not work for removing properties of
		/// subobjects. \todo does this make sense?
		virtual void removeProperty(const IPropertyView& property) = 0;

		// add/remove children
		/// adds a child property object. Sets the parent of \p child.
		/// \pre child->parent() == nullptr.
		/// \post child()->parent() == this.
		virtual void addChild( std::shared_ptr<IPropertyObject> child ) = 0;

		/// remove a child object that is registered here.
		/// \pre child.parent() == this.
		/// \post child.parent() == nullptr.
		virtual void removeChild( const IPropertyObject& child ) = 0;

		// notification
		// ---------------------------------------------------------
		/// \brief calls notifyIfChanged on all properties.
		/// \details This function triggers the change listeners for
		///			all registered properties, including those in subobjects.
		virtual void notifyAll() = 0;
		
		/// gets the property that is referred to by path (i.e. this can
		/// also access properties of child objects).
		/// this version of the function returns the internal shared_ptr.
		virtual const std::shared_ptr<IProperty>& getPropertyPtr(const std::string& path) const = 0;

	// protected:
	/// \todo figure out how to do access protection here
		/// sets the parent of this object
		virtual void setParent(const IPropertyObject* parent) noexcept = 0;
		
	};
}

#endif // IPROPERTYOBJECT_H_INCLUDED

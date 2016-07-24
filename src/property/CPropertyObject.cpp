#include "CPropertyObject.h"
#include "IProperty.h"
#include "CProperty.h"  /// for the copy algorithm. \todo move that elsewhere.
#include <algorithm>
#include <cassert>
#include <iostream>

namespace property
{
	CPropertyObject::CPropertyObject( std::string name ) : mName( std::move(name) )
	{

	}

	CPropertyObject::~CPropertyObject() noexcept
	{
		// CProperty objects are owned by their parent objects, so at this
		// point it should be unregistered.
	}

	const std::string& CPropertyObject::name() const noexcept
	{
		return mName;
	}

	/// gets a child property object of name \p name, or throws.
	/// only works for direct children.
	IPropertyObject& CPropertyObject::getChild(const std::string& name)
	{
		return *mChildren.at(name);
	}

	/// gets a child property object (const)of name \p name, or throws.
	/// only works for direct children.
	const IPropertyObjectView& CPropertyObject::getChild(const std::string& name) const
	{
		return *mChildren.at(name);
	}

	/// gets the parent property object, or nullptr if this
	/// is the root of the tree.
	const IPropertyObjectView* CPropertyObject::parent() const noexcept
	{
		return mParent;
	}

	/// adds a listener that is called whenever a new property is added.
	ListenerRef CPropertyObject::addInsertListener( listener_t listener )
	{
		return mInsertListeners.addListener( std::move(listener) );
	}

	/// adds a listener that is called whenever a property gets removed.
	ListenerRef CPropertyObject::addRemoveListener( listener_t listener )
	{
		return mRemoveListeners.addListener( std::move(listener) );
	}

	/// gets the property that is referred to by path (i.e. this can
	/// also access properties of child objects).
	IPropertyView& CPropertyObject::getProperty(const std::string& path) const
	{
		return *getPropertyPtr(path);
	}

	/// gets the property that is referred to by path (i.e. this can
	/// also access properties of child objects).
	/// this version of the function returns the internal shared_ptr.
	const std::shared_ptr<IProperty>& CPropertyObject::getPropertyPtr(const std::string& path) const
	{
		using namespace std;
		auto delim = find(path.begin(), path.end(), '.');
		if( delim == path.end())
		{
			return mProperties.at(path);
		}


		string subobj(path.begin(), delim);
		string rest(delim+1, path.end());
		return mChildren.at(subobj)->getPropertyPtr( move(rest) );
	}

	/// check if the property that is referred to by path (i.e. this can
	/// also access properties of child objects) exists.
	bool CPropertyObject::hasProperty(const std::string& path) const
	{
		using namespace std;
		auto delim = find(path.begin(), path.end(), '.');
		if( delim == path.end())
		{
			return mProperties.count(path) > 0;
		}


		string subobj(path.begin(), delim);
		string rest(delim+1, path.end());

		// check if correct child present
		if(mChildren.count(subobj) == 0)
			return false;

		// if yes, continue search
		return getChild(subobj).hasProperty( move(rest) );
	}

	/// check if this property object has \p child as a direct
	/// child node.
	bool CPropertyObject::hasChild(const std::string& child) const
	{
		return mChildren.count(child) != 0;
	}

	/// iterates over all properties and calls f for them.
	void CPropertyObject::forallProperties(const std::function<void(IPropertyView&)>& f, bool recurse) const
	{
		for(auto& prop : mProperties)
			f(*prop.second);

		if(recurse)
		{
			for(auto& child : mChildren)
				child.second->forallProperties(f);
		}
	}

	/// applies \p f to all immediate children of this property.
	void CPropertyObject::forallChildren( const std::function<void(const IPropertyObjectView&)>& f ) const
	{
		for(auto& child : mChildren)
			f(*child.second);
	}

	void CPropertyObject::setParent(const IPropertyObject* parent) noexcept
	{
		mParent = parent;
	}

	/// adds a property to this property objects.
	/// \pre property.owner() == this
	void CPropertyObject::addProperty(std::shared_ptr<IProperty> property)
	{
		assert( property->owner() == this );
		auto result = mProperties.insert({property->name(), std::move(property)});
		/// \todo check that we do not create duplicates!
	}

	/// removes a property from this property objects.
	/// this method does not work for removing properties of
	/// subobjects. \todo does this make sense?
	void CPropertyObject::removeProperty(const IPropertyView& property)
	{
		assert( property.owner() == this );
		mProperties.erase(property.name());
	}

	// add/remove children
	/// adds a child property object. Sets the parent of \p child.
	/// \pre child->parent() == nullptr.
	/// \post child()->parent() == this.
	void CPropertyObject::addChild( std::shared_ptr<IPropertyObject> child )
	{
		assert( child->parent() == nullptr );
		auto inserted = mChildren.insert({child->name(), std::move(child)});
		inserted.first->second->setParent(this);
		inserted.first->second->forallProperties([this](IPropertyView& view){ mInsertListeners.notify(view);});
	}

	/// remove a child object that is registered here.
	/// \pre child()->parent() == this.
	/// \post child->parent() == nullptr.
	void CPropertyObject::removeChild( const IPropertyObject& child )
	{
		assert( child.parent() == this );
		mChildren.erase( child.name() );
		const_cast<IPropertyObject&>(child).setParent(nullptr);
	}

	// notification
	// ---------------------------------------------------------
	/// \brief calls notifyIfChanged on all properties.
	/// \details This function triggers the change listeners for
	///			all registered properties, including those in subobjects.
	void CPropertyObject::notifyAll() const
	{
		for(auto& prop : mProperties)
			prop.second->notifyIfChanged();

		for(auto& child : mChildren)
			child.second->notifyAll();
	}


	/// \todo this refers directly to CPropertyObject
	void copyProperties(property::IPropertyObject& target, const property::IPropertyObjectView& source)
	{
		source.forallProperties([&](property::IPropertyView& view) mutable
		{
			if(target.hasProperty(view.name()))
			{
				*target.getPropertyPtr(view.name()) = view.value();
			} else
			{
				auto newprop = property::CProperty::create( view.name(), &target, view.value() );
			}
		}, false);

		// copy all children
		source.forallChildren([&](const property::IPropertyObjectView& view) mutable
		{
			if( target.hasChild(view.name()))
			{
				copyProperties(target.getChild(view.name()), view);
			} else {
				auto child = std::make_shared<property::CPropertyObject>( view.name() );
				target.addChild( child );
				copyProperties(*child, view);
			}
		});
	}
}

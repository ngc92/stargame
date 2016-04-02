#include "CPropertyObject.h"
#include "IPropertyView.h"
#include <algorithm>
#include <cassert>

namespace property
{
	std::string IPropertyObjectView::path() const
	{
		if(!parent())
			return name();

		return parent()->path() + "." + name();
	}


	CPropertyObject::CPropertyObject( std::string name ) : mName( std::move(name) )
	{

	}

	CPropertyObject::~CPropertyObject() noexcept
	{
		// make sure we unregister from parent!
		if(parent())
		{
			/// \todo check if this could throw!
			const_cast<IPropertyObject*>(mParent)->removeChild(this);
		}
	}

	const std::string& CPropertyObject::name() const noexcept
	{
		return mName;
	}

	/// gets a child property object of name \p name, or throws.
	/// only works for direct children.
	IPropertyObjectView& CPropertyObject::getChild(const std::string& name)
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
	IPropertyView& CPropertyObject::getProperty(std::string path) const
	{
		using namespace std;
		auto delim = find(path.begin(), path.end(), '.');
		if( delim == path.end())
		{
			auto& prop = mProperties.at(path);
			/// \todo what do we do when the property does not exist anymore?
			return *prop;
		}


        string subobj(path.begin(), delim);
        string rest(delim+1, path.end());
        return getChild(subobj).getProperty( move(rest) );
	}

	/// iterates over all properties and calls f for them.
	void CPropertyObject::forallProperties(const std::function<void(IPropertyView&)>& f) const
	{
		for(auto& prop : mProperties)
			f(*prop.second);

		for(auto& child : mChildren)
			child.second->forallProperties(f);
	}

	void CPropertyObject::setParent(const IPropertyObject* parent) noexcept
	{
		mParent = parent;
	}

	/// adds a property to this property objects.
	/// \pre property.owner() == this
	void CPropertyObject::addProperty(IPropertyView& property)
	{
		assert( property.owner() == this );
		mProperties.insert({property.name(), &property});
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
	void CPropertyObject::addChild( IPropertyObject* child )
	{
		assert( child->parent() == nullptr );
		mChildren.insert({child->name(), child});
		child->setParent(this);
		child->forallProperties([this](IPropertyView& view){ mInsertListeners.notify(view);});
	}

	/// remove a child object that is registered here.
	/// \pre child()->parent() == this.
	/// \post child->parent() == nullptr.
	void CPropertyObject::removeChild( IPropertyObject* child )
	{
		assert( child->parent() == this );
		mChildren.erase( child->name() );
		child->setParent(nullptr);
	}

	// notification
	// ---------------------------------------------------------
	/// \brief calls notifyIfChanged on all properties.
	/// \details This function triggers the change listeners for
	///			all registered properties, including those in subobjects.
	void CPropertyObject::notifyAll()
	{

	}
}

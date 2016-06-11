#include "CProperty.h"
#include "IPropertyObject.h"

namespace property
{
	std::string IPropertyView::path() const
	{
		if(!owner())
			return name();

		return owner()->path() + "." + name();
	}

	/// returns the name of the property
	const std::string& CProperty::name() const noexcept
	{
		return mName;
	}

	/// returns the property object that owns this property, or nullptr
	const IPropertyObject* CProperty::owner() const noexcept
	{
		return mOwner;
	}

	/// returns the value of the property as a variant
	auto CProperty::value() const noexcept -> const data_t&
	{
		return mData;
	}

	/// adds a listener to the property that will be triggered
	/// when the value of the property changes.
	ListenerRef CProperty::addListener( listener_t listener )
	{
		return mListeners.addListener( std::move(listener) );
	}

	/*! \brief notifies all change listeners and resets changed() status.
		\note Since the listener cannot modify the property value,
		we consider this method to be const. even though the changed status
		is reset.
	*/
	void CProperty::notify() const
	{
		const_cast<bool&>(mChanged) = false;
		mListeners.notify( (IProperty&)*this );
	}

	/// returns whether the value of the property was changed.
	bool CProperty::changed() const noexcept
	{
		return mChanged;
	}

	/// gets the value in a way that allows modification.
	/// calling this function sets the modification flag.
	auto CProperty::changable_value() noexcept -> data_t&
	{
		mChanged = true;
		return mData;
	}

	CProperty::CProperty(std::string name, const IPropertyObject* owner, data_t value):
		mName( std::move(name) ),
		mOwner( owner ),
		mData( std::move(value) )
	{
	}

	std::shared_ptr<CProperty> CProperty::create(std::string name, IPropertyObject* owner, data_t value)
	{
		auto shared = std::make_shared<CProperty>( access_ctor{}, std::move(name), owner, std::move(value) );
		if(owner)
		{
			owner->addProperty( shared );
		}

		return shared;
	}

}

#ifndef CPROPERTY_H_INCLUDED
#define CPROPERTY_H_INCLUDED

#include "IProperty.h"
#include "debug/ObjectCounter.h"
#include "util/ListenerList.h"

namespace property
{
    class CProperty: public IProperty, ObjectCounter<CProperty>
    {
	public:
        // property view:
        /// returns the name of the property
		const std::string& name() const noexcept final;
		/// returns the property object that owns this property, or nullptr
		const IPropertyObject* owner() const noexcept final;
		/// returns the value of the property as a variant
		const data_t& value() const	noexcept final;

		/// adds a listener to the property that will be triggered
		/// when the value of the property changes.
		ListenerRef addListener( listener_t listener ) final;

		// property
		/*! \brief notifies all change listeners and resets changed() status.
		 \note Since the listener cannot modify the property value,
		 we consider this method to be const. even though the changed status
		 is reset.
		*/
		void notify() const final;

		/// returns whether the value of the property was changed.
		bool changed() const noexcept final;

		/// gets the value in a way that allows modification.
		/// calling this function sets the modification flag.
		data_t& changable_value() final;

		/// constructor, takes a pre-generated variant and the future owner of the
		/// property. The property is automatically added to the owner.
		CProperty(std::string name, IPropertyObject* owner, data_t value);
	private:
		/// name of this property, cannot be changed later on
		const std::string mName;
		/// owner of this property, cannot be changed
		const IPropertyObject* const mOwner;
		/// content of the property
		data_t mData;
		/// change listeners
		ListenerList<IPropertyView&> mListeners;
		/// tracks whether data was changed since last listener call
		bool mChanged = false;
    };
}

#endif // CPROPERTY_H_INCLUDED

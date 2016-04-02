#ifndef IPROPERTY_H_INCLUDED
#define IPROPERTY_H_INCLUDED

#include "IPropertyView.h"
#include "util/ListenerList.h"

namespace property
{
	/*! \class IProperty
		\brief A property is a named value that provides a change listener.
		\details This class provides the full interface of a property, that
				is it extends the IPropertyView method by a notify
	*/
	class IProperty : public IPropertyView
	{
	public:
		/*! \brief notifies all change listeners and resets changed() status.
		 \note Since the listener cannot modify the property value,
		 we consider this method to be const. even though the changed status
		 is reset.
		*/
		virtual void notify() const = 0;

		/// returns whether the value of the property was changed.
		virtual bool changed() const noexcept = 0;

		/// class notify(), if changed() is true.
		/// \return whether or not notify() was called.
		bool notifyIfChanged() const;

		/// gets the value in a way that allows modification.
		/// calling this function sets the modification flag.
		virtual data_t& changable_value() = 0;

		/// assign a value and sets the changed flag.
		template<class T>
		IProperty& operator=(const T& value);
	};

	// implementations

	inline bool IProperty::notifyIfChanged() const
	{
		if(changed())
		{
			notify();
			return true;
		}
		return false;
	}

	template<class T>
	IProperty& IProperty::operator=(const T& value)
	{
		changable_value() = value;
		return *this;
	}
}



#endif // IPROPERTY_H_INCLUDED

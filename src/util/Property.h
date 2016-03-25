#ifndef PROPERTY_H_INCLUDED
#define PROPERTY_H_INCLUDED

#include "IProperty.h"

template<class T>
class Property final : public IProperty
{
public:
	Property(std::string name, const T& val) : IProperty(name), mValue(val)
	{
	};

	Property& operator=(const T& value )
	{
		mValue = value;
		setChanged();
		return *this;
	}
	operator const T&() const { return mValue; };

	// access
	const T& value() const { return mValue; };
private:
    T mValue;
};

// overload a few shortcut operators
/// \todo allow the use of +=, -= etc internally for more efficiency
template<class T, class U>
Property<T>& operator+=(Property<T>& p, U&& other)
{
	return p = p.value() + other;
}

template<class T, class U>
Property<T>& operator-=(Property<T>& p, U&& other)
{
	return p = p.value() - other;
}



#endif // PROPERTY_H_INCLUDED

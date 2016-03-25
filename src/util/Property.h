#ifndef PROPERTY_H_INCLUDED
#define PROPERTY_H_INCLUDED

#include "IProperty.h"

template<class T>
struct TypeDispatch;

template<>
struct TypeDispatch<int>
{
	static constexpr PropertyType type = PropertyType::INT;
};

template<>
struct TypeDispatch<float>
{
	static constexpr PropertyType type = PropertyType::FLOAT;
};


template<>
struct TypeDispatch<std::string>
{
	static constexpr PropertyType type = PropertyType::STRING;
};
template<class T>
class Property;

template<class U>
struct getter
{
	template<class T>
	static const U& get(const Property<T>& ) { assert(0); };

	static const U& get(const Property<U>& p ) { return p.value(); };
};

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
	PropertyType type() const override
	{
		return TypeDispatch<T>::type;
	}

	int getInt() const override 		{ return getter<int>::get(*this); };
	float getFloat() const override		{ return getter<float>::get(*this); };
	const std::string& getString() const override { return getter<std::string>::get(*this); };
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

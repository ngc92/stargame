#ifndef PROPERTY_H_INCLUDED
#define PROPERTY_H_INCLUDED

#include <string>

enum class PropertyTypes
{
    INT,
    FLOAT,
    STRING
};

class IProperty
{
public:
	IProperty(const IProperty&) = delete;
	IProperty& operator=(const IProperty&) = delete;

	/// returns whether the property was changed since
	/// change was reset last.
	bool changed() const { return mChanged; };

	/// returns the name of the property
	const std::string& name() const { return mName; };

	/// allows setting the changed state of the property
	void setChanged(bool changed = true)
	{
		mChanged = changed;
	}

	// access the saved value
protected:
	IProperty(std::string name) : mName(std::move(name)), mChanged(true)
	{
	}
private:
	std::string mName;
	bool mChanged;
};

template<class T>
class Property : public IProperty
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

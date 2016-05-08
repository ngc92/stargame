#ifndef TYPEDPROPERTY_H_INCLUDED
#define TYPEDPROPERTY_H_INCLUDED

#include <memory>
#include "IProperty.h"

namespace property
{
	/// helper function that creates a property object.
	std::shared_ptr<IProperty> make_property_default(std::string name, IPropertyObject* owner, data_t data);

	/*! \class TypedProperty
		\brief Type that mimics another type, but saves the value in a property.
		\details This class hides the details of a property behind a nice, strongly
				typed interface.
	*/
	template<class T>
	class TypedProperty final
	{
	public:
		/// constructor, takes an existing property
		TypedProperty(std::shared_ptr<IProperty> prop) : mProperty(std::move(prop)) {};

		/// constructor that creates a new property
		TypedProperty(std::string name, IPropertyObject* owner, const T& value):
			TypedProperty(std::move(name), owner, data_t(value))
		{
		}

		/// conversion to static type
		const T& convert() const { return boost::get<T>(mProperty->value()); };

		/// conversion operator
		operator const T&() const { return convert(); };

		/// assignment operator, only allows assignment of type T
		TypedProperty<T>& operator=(const T& value)
		{
			*mProperty = value;
			return *this;
		}
	private:
		/// constructor that creates a new property
		TypedProperty(std::string name, IPropertyObject* owner, data_t data):
			mProperty( make_property_default(std::move(name), owner, std::move(data)) )
		{

		}

		std::shared_ptr<IProperty> mProperty;
	};

	// --------------------------------------------------------
	//					operator overloads
	// --------------------------------------------------------

	template<class T, class U>
	TypedProperty<T>& operator+=(TypedProperty<T>& p, U&& other)
	{
		return p = (T)p + other;
	}

	template<class T, class U>
	TypedProperty<T>& operator-=(TypedProperty<T>& p, U&& other)
	{
		return p = (T)p - other;
	}
}

#endif // TYPEDPROPERTY_H_INCLUDED

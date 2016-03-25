#ifndef IPROPERTY_H_INCLUDED
#define IPROPERTY_H_INCLUDED

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

	// making this protected should ensure that we can never delete IProperty objects.
	~IProperty() = default;
private:
	const std::string mName;
	bool mChanged;
};


#endif // IPROPERTY_H_INCLUDED

#ifndef IPROPERTYOBJECT_H_INCLUDED
#define IPROPERTYOBJECT_H_INCLUDED

#include "IProperty.h"
#include "ListenerList.h"
#include <unordered_map>

class IPropertyCollection
{
public:
	typedef std::unordered_map<std::string, const IProperty*> PropertyMap;
	typedef ListenerList<const IProperty*> PropertyListener;

	virtual ~IPropertyCollection() = default;

	template<class T>
	void getPropertyNames(T&& out_iterator) const;

	const IProperty* getProperty( const std::string& name ) const
	{
		return getProperties().at(name);
	}

	template<class T>
    ListenerRef addPropertyChangeListener( const std::string& property, T&& listener );

	virtual void notifyIfChanged() const = 0;
private:
	virtual const PropertyMap& getProperties() const = 0;
	virtual PropertyListener& getListeners( const std::string& property ) = 0;
};

template<class T>
void IPropertyCollection::getPropertyNames(T&& out_iterator) const
{
	for(auto& p : getProperties())
	{
        *out_iterator = p.first;
        ++out_iterator;
	}
}

template<class T>
ListenerRef IPropertyCollection::addPropertyChangeListener( const std::string& property, T&& listener )
{
	return getListeners(property).addListener(listener);
}


// ------------------------------------------------------------------
// 	interface for an object that contains a property collection
// ------------------------------------------------------------------
class IPropertyObject
{
public:
	virtual ~IPropertyObject() = default;
	virtual const IPropertyCollection& properties() const = 0;
};



#endif // IPROPERTYOBJECT_H_INCLUDED

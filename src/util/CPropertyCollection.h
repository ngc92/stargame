#ifndef PROPERTYOBJECT_H_INCLUDED
#define PROPERTYOBJECT_H_INCLUDED

#include "IPropertyCollection.h"

class CPropertyCollection final : public IPropertyCollection
{
public:
	CPropertyCollection& addProperty(const IProperty* );
	CPropertyCollection& addProperty(const IProperty& o ) { return addProperty(&o); };
	void notifyIfChanged() const override;
private:
	const PropertyMap& getProperties() const override;
	PropertyListener& getListeners( const std::string& property ) override;

	PropertyMap mProperties;
	std::unordered_map<std::string, PropertyListener> mListeners;
};

#endif // PROPERTYOBJECT_H_INCLUDED

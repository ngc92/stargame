#include "CPropertyCollection.h"
#include <cassert>

const IPropertyCollection::PropertyMap& CPropertyCollection::getProperties() const
{
	return mProperties;
}

IPropertyCollection::PropertyListener& CPropertyCollection::getListeners( const std::string& property )
{
	return mListeners.at( property );
}

CPropertyCollection& CPropertyCollection::addProperty(const IProperty* prop)
{
	auto res = mProperties.emplace(prop->name(), prop);
	assert(res.second);
	mListeners.emplace(prop->name(), PropertyListener());
	return *this;
}

void CPropertyCollection::notifyIfChanged() const
{
    for( auto& prop : mProperties )
	{
		if(prop.second->changed())
		{
			/// \todo fix these const_casts, or write down why they are necessary.
			// we reset changed first, so if any of these calls lead to a change in properties,
			// we do not overwrite the change.
			const_cast<IProperty*>(prop.second)->setChanged(false);
            const_cast<PropertyListener&>(mListeners.at(prop.second->name())).notify( prop.second );
		}
	}
}

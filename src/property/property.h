#ifndef PROPERTY_H_INCLUDED
#define PROPERTY_H_INCLUDED

#include "IPropertyView.h"
#include "IPropertyObjectView.h"

/*! \namespace property
	\brief namespace that contains the property system.
	\details This includes properties (IProperty) and views
			 (IPropertyView) as well as the corresponding
			 classed for the property hierarchy (IPropertyObject,
			 IPropertyObjectView). Furthermore, default
			 iplementations (CProperty, CPropertyObject)
			 are provided. These are virtually derived from
			 the interfaces and can thus be used as drop-in
			 base classes.
*/
namespace property
{
	class IPropertyObject;
	class IProperty;
}


#endif // PROPERTY_H_INCLUDED

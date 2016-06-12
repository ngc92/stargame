#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <iosfwd>

namespace property
{
	class IProperty;
	class IPropertyObject;
	
	class IPropertyObjectView;
	class IPropertyView;
	
	std::ostream& operator<<(std::ostream& stream, const IPropertyObjectView& property);
	std::ostream& operator<<(std::ostream& stream, const IPropertyView& property);
}

#endif // IO_H_INCLUDED

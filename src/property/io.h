#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <iosfwd>

namespace property
{
	class IProperty;
	class IPropertyObject;
	
	std::ostream& operator<<(std::ostream& stream, const IPropertyObjectView& property);
}

namespace boost
{
	namespace serialization
	{
		template<class Archive>
		void serialize(Archive & ar, property::IPropertyObject & t, const unsigned int file_version)
		{
		}
	}
}


#endif // IO_H_INCLUDED

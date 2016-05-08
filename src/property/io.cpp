#include "property.h"
#include "IPropertyObjectView.h"
#include "util/io.h"
#include <iostream>

namespace property
{
	std::ostream& operator<<(std::ostream& stream, const IPropertyObjectView& property)
	{
		stream << property.name() << ":\n";
		property.forallProperties( [&](const IPropertyView& view)
		{
			stream << " " << view.path() << " = " << view.value() << "\n";
		} );
		return stream;
	}
}

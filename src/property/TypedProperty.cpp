#include "TypedProperty.h"
#include "CProperty.h"

namespace property
{
	std::shared_ptr<IProperty> make_property_default(std::string name, IPropertyObject* owner, data_t data)
	{
		return CProperty::create(std::move(name), owner, std::move(data));
	}
}

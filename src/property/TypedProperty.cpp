#include "TypedProperty.h"
#include "CProperty.h"

namespace property
{
	std::shared_ptr<IProperty> make_property_default(std::string name, IPropertyObject* owner, IProperty::data_t data)
	{
        return std::make_shared<CProperty>(std::move(name), owner, std::move(data));
	}
}

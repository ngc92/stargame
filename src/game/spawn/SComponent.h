#ifndef SCOMPONENT_H_INCLUDED
#define SCOMPONENT_H_INCLUDED

#include "Definitions.h"

namespace property
{
	class IPropertyObject;
}

namespace game
{
namespace spawn
{
	/// component definition.
	class SComponent
	{
	public:
		SComponent( const boost::property_tree::ptree& props );

		// data getters
		const std::string& type() const;
		float HP() const;
		float weight() const;

		const property::IPropertyObject& getProperties() const;

		std::shared_ptr<IComponent> create() const;
	private:
		std::string mType;
		float mHitPoints;
		float mWeight;
		std::shared_ptr<property::IPropertyObject> mProperties;
	};

	}
}

#endif // SCOMPONENT_H_INCLUDED

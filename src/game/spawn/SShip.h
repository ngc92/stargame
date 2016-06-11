#ifndef SSHIP_H_INCLUDED
#define SSHIP_H_INCLUDED

#include "Definitions.h"

namespace game
{
namespace spawn
{
	class SShip
	{
		struct cmpdef
		{
			std::string type;
			int cell;
		};
		typedef std::vector<cmpdef> cmp_vec_t;
	public:
		SShip(const boost::property_tree::ptree& props);

		const std::string& hull() const;
		const std::string& name() const;
		const cmp_vec_t& components() const;

		void addAttributes( property::IPropertyObject& obj ) const;
	private:
		std::string mHull;
		std::string mName;

		std::vector<cmpdef> mComponents;
		std::unordered_map<std::string, std::string> mAttributes;
	};
}
}

#endif // SSHIP_H_INCLUDED

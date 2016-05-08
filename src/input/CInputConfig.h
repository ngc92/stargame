#ifndef CINPUTCONFIG_H_INCLUDED
#define CINPUTCONFIG_H_INCLUDED

#include "IInputConfiguration.h"
#include <unordered_map>
#include <memory>
#include <boost/property_tree/ptree_fwd.hpp>

namespace input
{
	class CInputConfig : public IInputConfig
	{
	public:
		CInputConfig();
		~CInputConfig();
		void load() override;

		/// creates an input element that manipulates \p property, if specified.
		/// \return pointer to the newly created input element, or nullptr if none could be created.
		std::shared_ptr<IInputElement> getInputElemt( const property::IPropertyView& property ) override;
	private:
		using ptree_ptr = std::unique_ptr<boost::property_tree::ptree>;
		std::unordered_map<std::string, ptree_ptr> mMappingRules;
	};
}

#endif // CINPUTCONFIG_H_INCLUDED

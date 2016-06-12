#include "InputElements.h"
#include "CInputGauge.h"
#include "CInputButton.h"

#include "game/view_thread/IViewThreadGO.h"

#include <boost/property_tree/ptree.hpp>

#include <iostream>

namespace input
{
	// --------------------------------------------------------
	// 						factory function
	// --------------------------------------------------------
	std::shared_ptr<IInputElement> createInputElement(  boost::property_tree::ptree& props,
														const property::IPropertyView& property )
	{
		auto cowner = dynamic_cast<const game::view_thread::IViewThreadGameObject*>(property.owner()->root());
		auto owner = const_cast<game::view_thread::IViewThreadGameObject*>(cowner);
		std::string type = props.get<std::string>("type");
		if( type == "gauge" )
		{
			int increase = props.get<int>("increase", -1);
			int decrease = props.get<int>("decrease", -1);
			float minimum = props.get<float>("minimum", 0.f);
			float maximum = props.get<float>("maximum", 1.f);
			std::string path = property.path();
			/// \todo this is very ugly, maybe we can get rid of that soon.
			// the path contains the name of the object itself, so to access, we need to remove that!
			path = path.substr(path.find('.')+1);
			return std::make_shared<CInputGauge>(path, owner, increase, decrease, minimum, maximum);
		} else if( type == "button" )
		{
			float def_val = props.get<float>("default", 0.f);
			std::string path = property.path();
			/// \todo this is very ugly, maybe we can get rid of that soon.
			// the path contains the name of the object itself, so to access, we need to remove that!
			path = path.substr(path.find('.')+1);
			auto element = std::make_shared<CInputButton>(path, owner, def_val);
			for(auto& value : props)
			{
				if(value.first == "state")
				{
					int key = value.second.get<int>("key");
					float val = value.second.get<float>("value");
					element->addButtonState(key, val);
				}
			}
			return element;
		}

		return nullptr;
	}
}

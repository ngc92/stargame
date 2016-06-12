#ifndef INPUTELEMENTS_H_INCLUDED
#define INPUTELEMENTS_H_INCLUDED

#include "IInputElement.h"

namespace input
{
	std::shared_ptr<IInputElement> createInputElement( 	boost::property_tree::ptree& props,
														const property::IPropertyView& property );
}

#endif // INPUTELEMENTS_H_INCLUDED

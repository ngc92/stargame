#ifndef CINPUTELEMENT_H_INCLUDED
#define CINPUTELEMENT_H_INCLUDED

#include "IInputElement.h"

namespace input
{
    class CInputElement: public virtual IInputElement
    {
	public:
		CInputElement(std::string path);
	protected:
		std::function<void(game::IGameObject&)> setValue( float value );
		
		std::string mPropertyPath;
	};
}

#endif // CINPUTELEMENT_H_INCLUDED

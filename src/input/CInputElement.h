#ifndef CINPUTELEMENT_H_INCLUDED
#define CINPUTELEMENT_H_INCLUDED

#include "IInputElement.h"

namespace game
{
	namespace view_thread
	{
		class IViewThreadGameObject;
	}
}

namespace input
{
    class CInputElement: public virtual IInputElement
    {
	public:
		CInputElement(std::string path, game::view_thread::IViewThreadGameObject* object);
	protected:
		void setValue( float value );
		
		std::string mPropertyPath;
		game::view_thread::IViewThreadGameObject* mObject;
	};
}

#endif // CINPUTELEMENT_H_INCLUDED

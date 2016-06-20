#include "CInputElement.h"

namespace input
{
	CInputElement::CInputElement(std::string path, game::view_thread::IViewThreadGameObject* object) :
		mPropertyPath( std::move(path) ), mObject( object )
	{

	}

	void CInputElement::setValue( float value )
	{
//		mObject->setProperty(  mPropertyPath, value );
	}
}

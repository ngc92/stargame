#include "CInputElement.h"
#include "game/IGameObject.h"
#include "property/IProperty.h"

namespace input
{
	CInputElement::CInputElement(std::string path) :
		mPropertyPath( std::move(path) )
	{

	}

	std::function<void(game::IGameObject&)> CInputElement::setValue( float value )
	{
		/// \todo somewhat ugly here.
		return [path=mPropertyPath, value](game::IGameObject& object){ object.getPropertyPtr(path)->assign(value); };
	}
}

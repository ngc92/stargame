#include "TextInterface.h"
#include <iostream>
#include "game/GameWorld.h"
#include "game/GameObject.h"

void TextInterface::update(const game::GameWorld& view)
{
	std::cout << "UPDATE INTERFACE!\n";
	view.iterateViews([this](const game::GameObject& o){ this->handleObject(o);} );
}

void TextInterface::handleObject( const game::GameObject& view )
{
	std::cout << "GameObject " << view.getID() << " at position "
			  << view.getPosition().x << ", " << view.getPosition().y << " angle " << view.getRotation() << "\n";
	view.iterateProperties([](const std::string& name, IPropertyObject* pob)
	{
		std::cout << "PROPERTY SET: " << name << "\n";
		std::vector<std::string> names;
		pob->properties().getPropertyNames( std::back_inserter(names) );
		for(auto& name : names)
		{
			std::cout << " " << name << ": ";
			const IProperty* prob = pob->properties().getProperty( name );
			switch(prob->type())
			{
			case PropertyType::INT:
				std::cout <<prob->getInt() << ", ";
				break;
			case PropertyType::FLOAT:
				std::cout <<prob->getFloat() << ", ";
				break;
			case PropertyType::STRING:
				std::cout <<prob->getString() << ", ";
				break;
			}
		}
	});
}

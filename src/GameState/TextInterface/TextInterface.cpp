#include "TextInterface.h"
#include <iostream>
#include "game/GameWorld.h"
#include "game/GameObject.h"
#include "property/property.h"

void TextInterface::onStep(const game::GameWorld& view)
{
	view.iterateViews([this](const game::GameObject& o){ this->handleObject(o);} );
}

void TextInterface::onSpawn( const game::GameObject& spawned )
{
	std::cout << "ON SPAWN\n";
	spawned.forallProperties([](property::IPropertyView& prop)
	{
		std::cout << "PROPERTY: " << prop.path() << " = ";
		std::cout << prop.value() << "\n";
	});
}

void TextInterface::handleObject( const game::GameObject& view )
{
	std::cout << "GameObject " << view.getID() << " at position "
			  << view.getPosition().x << ", " << view.getPosition().y << " angle " << view.getRotation() << "\n";
}

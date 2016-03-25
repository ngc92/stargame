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
}

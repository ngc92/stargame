#include "TextInterface.h"
#include <iostream>
#include "game/IGameWorld.h"
#include "game/IGameObject.h"
#include "property/property.h"
#include <functional>


void TextInterface::init(game::IGameWorldView& world_view)
{
	using namespace std::placeholders;

	mSpawnLst = world_view.addSpawnListener(std::bind(&TextInterface::onSpawn, this, _1));
}

void TextInterface::step(game::IGameWorldView& world_view)
{
	world_view.iterateAllObjects([this](const game::IGameObjectView& o){ this->handleObject(o);});
}

void TextInterface::onSpawn( const game::IGameObjectView& spawned )
{
	std::cout << "ON SPAWN\n";
	std::cout << spawned << "\n";
}


void TextInterface::handleObject( const game::IGameObjectView& view )
{
	std::cout << "GameObject " << view.id() << " at position "
			  << view.position().x << ", " << view.position().y << " angle " << view.angle() << "\n";
}


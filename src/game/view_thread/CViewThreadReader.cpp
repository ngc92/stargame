#include "CViewThreadReader.h"
#include "SpawnEvent.h"
#include "EventStream.h"
#include "game/IGameWorldView.h"
#include "game/IGameObjectView.h"
#include "CViewThreadGO.h"
#include "game/IGameWorld.h"
#include <iostream>
#include "util/io.h"
#include "property/io.h"

namespace game
{
namespace view_thread
{
	struct EventHandler : public boost::static_visitor<void>
	{
		EventHandler(CViewThreadReader& rd,IGameWorld& w) : reader(rd), world(w) {}
		CViewThreadReader& reader;
		IGameWorld& world;
		void operator()(const SpawnEvent& spev)
		{
			reader.onSpawn(world, spev);
		}

		void operator()(const DespawnEvent& spev)
		{
		}

		void operator()(const UpdateEvent& spev)
		{
		}
	};

	CViewThreadReader::CViewThreadReader(IEventStreamReader& stream) : mBuffer( stream )
	{

	}

	void CViewThreadReader::init( IGameWorld& world )
	{
	}

	void CViewThreadReader::step( IGameWorld& world )
	{
		mBuffer.update();
		std::cout << "READ " << mBuffer.read().size() << "\n";

		EventHandler visit = {*this, world};
		for(auto& event : mBuffer.read())
		{
			std::cout << "e: " << event.which() << "\n";
			boost::apply_visitor(visit, event);
		}
	}

	void CViewThreadReader::onSpawn( IGameWorld& world, const SpawnEvent& event )
	{
		std::cout << "\a";
		auto spawned_object = std::make_shared<CViewThreadGameObject>(-1);
		// copy all properties
		copyProperties(*spawned_object, event.properties());


		//props.forallProperties([](auto& p){ std::cout << p << "\n"; });
		world.addGameObject(spawned_object);
	}
}
}

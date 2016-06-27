#include "CViewThreadReader.h"
#include "SpawnEvent.h"
#include "EventStream.h"
#include "game/IGameWorldView.h"
#include "game/IGameObjectView.h"
#include "game/IGameObject.h"
#include "game/IGameWorld.h"
#include "game/spawn/ISpawnManager.h"
#include "game/physics/body.h"
#include <iostream>
#include "util/io.h"
#include "property/io.h"

namespace game
{
namespace view_thread
{
	struct EventHandler : public boost::static_visitor<void>
	{
		EventHandler(CViewThreadReader& rd, IGameWorld& w, const spawn::ISpawnManager& s) : reader(rd), spawner(s), world(w) {}
		CViewThreadReader& reader;
		const spawn::ISpawnManager& spawner;
		IGameWorld& world;
		void operator()(const SpawnEvent& spev)
		{
			reader.onSpawn(world, spawner, spev);
		}

		void operator()(const DespawnEvent& spev)
		{
		}

		void operator()(const UpdateEvent& uev)
		{
			reader.onUpdate( world, uev );
		}
	};

	CViewThreadReader::CViewThreadReader(IEventStreamReader& stream) : mBuffer( stream )
	{

	}

	void CViewThreadReader::init( IGameWorld& world )
	{
	}

	void CViewThreadReader::step( IGameWorld& world, const spawn::ISpawnManager& spawner )
	{
		mBuffer.update();
		//std::cout << "READ " << mBuffer.read().size() << "\n";

		EventHandler visit = {*this, world, spawner};
		for(auto& event : mBuffer.read())
		{
			boost::apply_visitor(visit, event);
		}
	}

	void CViewThreadReader::onSpawn( IGameWorld& world, const spawn::ISpawnManager& spawner, const SpawnEvent& event )
	{
		auto spawned_object = spawner.spawn(world, event.spawn_data());
		// copy all properties
		copyProperties(*spawned_object, event.properties());
	}

	void CViewThreadReader::onUpdate( IGameWorld& world, const UpdateEvent& event )
	{
		IGameObject& target = world.getObjectByID( event.id );
		target.getBody().setAngle( event.angle );
		target.getBody().setPosition( event.position );
		target.getBody().setVelocity( event.velocity );
		target.getBody().setAngularVelocity( event.angular_velocity );
	}
}
}

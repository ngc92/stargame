#include "CSimulationThreadWriter.h"
#include "SpawnEvent.h"
#include "game/IGameWorldView.h"
#include "game/IGameObjectView.h"
#include "EventStream.h"
#include <iostream>
#include "util/io.h"

namespace game
{
namespace view_thread
{
	CSimulationThreadWriter::CSimulationThreadWriter(IEventStreamWriter& writer) :
		mBuffer(writer)
	{

	}

	void CSimulationThreadWriter::step( IGameWorldView& world_view )
	{
		std::cout << "step ";
//		std::cout << mBuffer.cache_size() << " -> ";
		world_view.iterateAllObjects([this](IGameObjectView& object){pushObjectUpdate(object);});
		std::cout << mBuffer.publish() << "\n";

	}

	void CSimulationThreadWriter::init( IGameWorldView& world_view )
	{
		// set up the spawn listener
		mSpawnListener = world_view.addSpawnListener([this](IGameObjectView& spawned) mutable { onSpawn(spawned); });
	}

	void CSimulationThreadWriter::onSpawn( IGameObjectView& object )
	{
		// create a unique id for that object
		std::uint64_t uuid = ++mUUID_counter;
		std::cout << "ON_SPAWN\a: " << uuid << "\n";

		// add a change listener to all properties.
		object.forallProperties(
			[this](property::IPropertyView& prop)
			{
				prop.addListener([this](property::IPropertyView& changed) { pushPropertyUpdate(changed); });
			});

		// and built a spawn event
		SpawnEvent event(object);
		mBuffer.push( std::move(event) );
	}

	void CSimulationThreadWriter::pushPropertyUpdate( property::IPropertyView& property )
	{
		std::string path = property.path(); // this operation allocates a string, so it is potentially slow
	}

	void CSimulationThreadWriter::pushObjectUpdate( const IGameObjectView& object )
	{
		UpdateEvent update;
		update.position = object.position();
		update.velocity = object.velocity();
		update.angle = object.angle();
		update.angular_velocity = object.angular_velocity();
		mBuffer.push( std::move(update) );
	}
}
}

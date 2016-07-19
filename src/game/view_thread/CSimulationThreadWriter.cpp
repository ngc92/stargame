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
//		std::cout << "step ";
//		std::cout << mBuffer.cache_size() << " -> ";
		world_view.iterateAllObjects([this](IGameObjectView& object){ pushObjectUpdate(object);} );
//		std::cout << mBuffer.publish() << "\n";
		mBuffer.publish();

	}

	void CSimulationThreadWriter::init( IGameWorldView& world_view )
	{
		// set up the spawn listener
		mSpawnListener = world_view.addSpawnListener([this](IGameObjectView& spawned) mutable { onSpawn(spawned); });
	}

	void CSimulationThreadWriter::onSpawn( IGameObjectView& object )
	{
		// create a unique id for that object
		std::uint64_t uuid = object.id();
		std::vector<ListenerRef> reglist;

		// add a change listener to all properties.
		object.forallProperties(
			[this, &reglist, uuid](property::IPropertyView& prop)
			{
				auto lst = prop.addListener([this, uuid](property::IPropertyView& changed) { pushPropertyUpdate(uuid, changed); });
				reglist.push_back( lst );
			});

		// and built a spawn event
		SpawnEvent event(object);
		mBuffer.push( std::move(event) );
		
		// move all registered listeners into a remove listener, so they stay registered until the object gets removed
		auto remlist = object.addRemoveListener([listeners = std::move(reglist), this]( const IGameObjectView& object )
												{
													onDespawn(object.id());
												});
		mRemoveListeners[object.id()] = std::move(remlist);
	}

	void CSimulationThreadWriter::pushPropertyUpdate( uint64_t id, property::IPropertyView& property )
	{
		std::string path = property.path(); // this operation allocates a string, so it is potentially slow
		PropertyEvent pevent = {id, std::move(path), property.value()};
		mBuffer.push( std::move(pevent) );
	}

	void CSimulationThreadWriter::pushObjectUpdate( const IGameObjectView& object )
	{
		UpdateEvent update;
		update.id = object.id();
		update.position = object.position();
		update.velocity = object.velocity();
		update.angle = object.angle();
		update.angular_velocity = object.angular_velocity();
		mBuffer.push( std::move(update) );
	}
	
	void CSimulationThreadWriter::onDespawn( uint64_t id )
	{
		mRemoveListeners.erase( mRemoveListeners.find(id) );
		mBuffer.push( DespawnEvent{id} );
	}
}
}

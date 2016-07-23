#ifndef CSIMULATIONTHREADWRITER_H_INCLUDED
#define CSIMULATIONTHREADWRITER_H_INCLUDED

#include "game/IGameViewModule.h"
#include "property/IPropertyView.h"
#include "util/buffered_thread_stream.h"
#include "UpdateEvent.h"
#include "ThreadStreams.h"
#include <unordered_map>

namespace game
{
namespace threading
{
	class CSimulationThreadWriter : public IGameViewModule
	{
	public:
		CSimulationThreadWriter(IThreadStreamWriter<Event>& writer);

		void step( IGameWorldView& world_view ) override;

		void init( IGameWorldView& world_view ) override;

	private:
		void onSpawn( IGameObjectView& object );
		void onDespawn( uint64_t id );

		void pushPropertyUpdate( uint64_t id, property::IPropertyView& property );
		void pushObjectUpdate( const IGameObjectView& object );

		ListenerRef mSpawnListener;
		std::unordered_map<uint64_t, ListenerRef> mRemoveListeners;

		IThreadStreamWriter<Event>& mBuffer;
	};
}
}

#endif // CSIMULATIONTHREADWRITER_H_INCLUDED

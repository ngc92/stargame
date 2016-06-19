#ifndef CSIMULATIONTHREADWRITER_H_INCLUDED
#define CSIMULATIONTHREADWRITER_H_INCLUDED

#include "game/IGameViewModule.h"
#include "property/IPropertyView.h"
#include "util/buffered_thread_stream.h"
#include "UpdateEvent.h"

namespace game
{
namespace view_thread
{
	class IEventStreamWriter;
	class CSimulationThreadWriter : public IGameViewModule
	{
	public:
		CSimulationThreadWriter(IEventStreamWriter& writer);

		void step( IGameWorldView& world_view ) override;

		void init( IGameWorldView& world_view ) override;

	private:
		void onSpawn( IGameObjectView& object );

		void pushPropertyUpdate( property::IPropertyView& property );
		void pushObjectUpdate( const IGameObjectView& object );

		std::uint64_t mUUID_counter = 0;

		ListenerRef mSpawnListener;

		IEventStreamWriter& mBuffer;
	};
}
}

#endif // CSIMULATIONTHREADWRITER_H_INCLUDED

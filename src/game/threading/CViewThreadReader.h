#ifndef CVIEWTHREADREADER_H_INCLUDED
#define CVIEWTHREADREADER_H_INCLUDED


#include "game/IGameViewModule.h"
#include "property/IPropertyView.h"
#include "util/buffered_thread_stream.h"
#include "UpdateEvent.h"
#include "ThreadStreams.h"

namespace game
{
namespace threading
{
	class CViewThreadReader : public IGameModule
	{
	public:
		CViewThreadReader(IThreadStreamReader<Event>& stream);

		void step( IGameWorld& world, const spawn::ISpawnManager& spawner ) override;

		void init( IGameWorld& world_view ) override;

		// event handler functions
		void onSpawn( IGameWorld& world, const spawn::ISpawnManager& spawner, const SpawnEvent& event );
		void onDespawn( IGameWorld& world, const DespawnEvent& event );
		void onUpdate( IGameWorld& world, const UpdateEvent& event );
		void onPropertyUpdate( IGameWorld& world, const PropertyEvent& event );

	private:
		IThreadStreamReader<Event>& mBuffer;
	};
}
}

#endif // CVIEWTHREADREADER_H_INCLUDED

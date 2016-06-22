#ifndef CVIEWTHREADREADER_H_INCLUDED
#define CVIEWTHREADREADER_H_INCLUDED


#include "game/IGameViewModule.h"
#include "property/IPropertyView.h"
#include "util/buffered_thread_stream.h"
#include "UpdateEvent.h"

namespace game
{
namespace view_thread
{
	class IEventStreamReader;
	class CViewThreadReader : public IGameModule
	{
	public:
		CViewThreadReader(IEventStreamReader& stream);

		void step( IGameWorld& world, const spawn::ISpawnManager& spawner ) override;

		void init( IGameWorld& world_view ) override;

		// event handler functions
		void onSpawn( IGameWorld& world, const spawn::ISpawnManager& spawner, const SpawnEvent& event );
		void onUpdate( IGameWorld& world, const UpdateEvent& event );

	private:
		IEventStreamReader& mBuffer;
	};
}
}

#endif // CVIEWTHREADREADER_H_INCLUDED

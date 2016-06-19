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
	class CViewThreadReader : public IGameViewModule
	{
	public:
		CViewThreadReader(IEventStreamReader& stream);

		void step( IGameWorldView& world_view ) override;

		void init( IGameWorldView& world_view ) override;

	private:

		std::uint64_t mUUID_counter = 0;

		IEventStreamReader& mBuffer;
	};
}
}

#endif // CVIEWTHREADREADER_H_INCLUDED

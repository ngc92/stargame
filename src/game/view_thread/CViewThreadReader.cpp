#include "CViewThreadReader.h"
#include "SpawnEvent.h"
#include "EventStream.h"
#include "game/IGameWorldView.h"
#include "game/IGameObjectView.h"
#include <iostream>
#include "util/io.h"

namespace game
{
namespace view_thread
{
	CViewThreadReader::CViewThreadReader(IEventStreamReader& stream) : mBuffer( stream )
	{

	}

	void CViewThreadReader::init( IGameWorldView& world_view )
	{
	}

	void CViewThreadReader::step( IGameWorldView& world_view )
	{
		mBuffer.update();
		std::cout << "READ " << mBuffer.read().size() << "\n";

		for(auto& event : mBuffer.read())
		{

		}

	}
}
}

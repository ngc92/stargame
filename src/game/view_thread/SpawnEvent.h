#ifndef SPAWNEVENT_H_INCLUDED
#define SPAWNEVENT_H_INCLUDED

#include <memory>
#include "game/spawn/SpawnData.h"

namespace property
{
	class IPropertyObject;
}

namespace game
{
class IGameObjectView;
namespace view_thread
{
	/*! \brief This event transfers game objects from the simuation word to the view world.
		\details This means most likely that a new object spawn, but we can use it also
				to transmit an initial state. Since events of this type are relatively
				infrequent, it is OK that the SpawnEvent dynamically allocates memory.
	*/
	class SpawnEvent
	{
	public:
		/// constructor. makes a copy of all values of properties that are
		/// saved inside \p spawned so it can be reconstructed.
		SpawnEvent( IGameObjectView& spawned );

		const property::IPropertyObject& properties() const;
		spawn::SpawnData& spawn_data() { return mSpawnData; }
		const spawn::SpawnData& spawn_data() const { return mSpawnData; }
	private:
		std::shared_ptr<property::IPropertyObject> mProperties;
		spawn::SpawnData mSpawnData;
	};
}
}

#endif // SPAWNEVENT_H_INCLUDED

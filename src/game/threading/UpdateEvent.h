#ifndef UPDATEEVENT_H_INCLUDED
#define UPDATEEVENT_H_INCLUDED

#include "property/property.h"
#include "game/spawn/SpawnData.h"

namespace game
{
class IGameObjectView;
namespace threading
{
	/*! created for every object every frame, updates physics data */
	struct UpdateEvent
	{
		uint64_t id;
		b2Vec2 position;
		b2Vec2 velocity;
		float angle;
		float angular_velocity;
	};

	/*! \brief Notify object despawn */
	struct DespawnEvent
	{
		uint64_t id;
	};
	
	/*! \brief This event notifies that a property has been changed.
		\details Contains the ID of the object, the path to the property
				and the new value.
	*/
	struct PropertyEvent
	{
		uint64_t id;			//!< ID of the associated game object
		std::string path;		//!< full path of the changed property
		property::data_t value;	//!< new value of the property.
	};
	
	struct AddPropertyEvent
	{
		uint64_t id;				//!< ID id of the associated game object.
		std::string path;			//!< Full path of the new property.
		property::data_t value;		//!< Value of the new property.
	};
	
	/*! \brief This event transfers game objects from the simulation word to the view world.
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

	using Event = boost::variant<UpdateEvent, SpawnEvent, DespawnEvent, PropertyEvent, AddPropertyEvent>;
}
}

#endif // UPDATEEVENT_H_INCLUDED

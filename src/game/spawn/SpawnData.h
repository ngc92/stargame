#ifndef SPAWNDATA_H_INCLUDED
#define SPAWNDATA_H_INCLUDED

#include <Box2D/Common/b2Math.h>
#include <string>
#include <functional>

namespace game
{
	class IGameObject;
	class IGameObjectView;
	class IGameWorld;
	enum class ObjectCategory : int;

	namespace spawn
	{
		class ISpawnManager;

		/*! \struct SpawnData
			\brief This struct collects all necessary information to create a
					new game object in one place.
			\details It provides setter methods for all members that return
					a reference to the object itself, allowing for convenient
					chaining.
		*/
		struct SpawnData
		{
			/// create a spawn data object. needs at least category, type and position.
			SpawnData( ObjectCategory category, std::string type, b2Vec2 pos );

			/// create a spawn data object that copies info from existing object.
			SpawnData( const IGameObjectView& source );

			ObjectCategory category;								//!< category of the object to be spawned.
			std::string type;								//!< type identifying the new object.
			b2Vec2 position;								//!< initial position.
			b2Vec2 velocity           = b2Vec2(0, 0);		//!< initial velocity.
			float angle               = 0.f;				//!< initial angle.
			float angular_velocity    = 0.f;				//!< initial angular velocity.
			uint64_t id               = -1;					//!< object id. immutable after creation.
			std::string name          = "object";			//!< object name. immutable after creation.

			const IGameObject* origin = nullptr;			//!< subordinate object of origin

			// function for setting non-default values
			SpawnData& set_type( std::string type_ ) { type = std::move(type_); return *this; }
			SpawnData& set_id( uint64_t id_ ) { id = id_; return *this; }
			SpawnData& set_angle( float angle_ ) { angle = angle_; return *this; }
			SpawnData& set_angular_velocity( float angular_velocity_ ) { angular_velocity = angular_velocity_; return *this; }
			SpawnData& set_position( const b2Vec2& position_ ) { position = position_; return *this; }
			SpawnData& set_velocity( const b2Vec2& velocity_ ) { velocity = velocity_; return *this; }
			SpawnData& set_name( std::string name_ ) { name = std::move(name_); return *this; }
		};

		// -------------------------------------------------------------------
		//		some useful functions to work with spawn data
		// -------------------------------------------------------------------
		SpawnData& subordinate( SpawnData& data, const IGameObject& parent );

		std::function<void(IGameWorld&, const ISpawnManager&)> make_spawner( SpawnData data );
	}
}

#endif // SPAWNDATA_H_INCLUDED

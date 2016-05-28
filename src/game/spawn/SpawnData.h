#ifndef SPAWNDATA_H_INCLUDED
#define SPAWNDATA_H_INCLUDED

#include <Box2D/Common/b2Math.h>
#include <string>

class b2BodyDef;

namespace game
{
	class IGameObject;
	
	namespace spawn
	{
		//! the different categories of things we can spawn
		enum class SpawnType
		{
			SPACESHIP,
			BULLET
		};
		
		/*! \struct SpawnData
			\brief This struct collects all necessary information to create a 
					new game object in one place.
		*/
		struct SpawnData
		{
			/// create a spawn data object. needs at least category, type and position.
			SpawnData( SpawnType category, std::string type, b2Vec2 pos );
			
			SpawnType category;								//!< category of the object to be spawned.
			std::string type;								//!< type identifying the new object.
			b2Vec2 position;								//!< initial position.
			b2Vec2 velocity           = b2Vec2(0, 0);		//!< initial velocity.
			float angle               = 0.f;				//!< initial angle.
			float angular_velocity    = 0.f;				//!< initial angular velocity.
			long id                   = -1;					//!< object id.
			
			const IGameObject* origin = nullptr;			//!< subordinate object of origin
			
			// function for setting non-default values
			SpawnData& set_id( long id_ ) { id = id_; return *this; }
			SpawnData& set_angle( float angle_ ) { angle = angle_; return *this; }
		};
		
		// -------------------------------------------------------------------
		//		some useful functions to work with spawn data
		// -------------------------------------------------------------------
		b2BodyDef body_def( const SpawnData& );
		
		SpawnData& subordinate( SpawnData& data, const IGameObject& parent );
	}
}

#endif // SPAWNDATA_H_INCLUDED

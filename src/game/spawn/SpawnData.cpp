#include "SpawnData.h"
#include "ISpawnManager.h"
#include "game/IGameObject.h"
#include "game/physics/body.h"
#include "game/physics/convert.h"
#include <Box2D/Dynamics/b2Body.h>

namespace game
{
namespace spawn
{
	SpawnData::SpawnData( ObjectCategory category_, std::string type_, b2Vec2 pos_ ) :
		category( category_ ),
		type( std::move(type_) ),
		position( std::move(pos_) )
	{

	}

	SpawnData::SpawnData( const IGameObjectView& source ):
		category( source.category() ),
		type( source.type() ),
		position( source.position() ),
		velocity( source.velocity() ),
		angle( source.angle() ),
		angular_velocity( source.angular_velocity() ),
		id( source.id() ),
		name( source.name() )
	{

	}

	b2BodyDef body_def( const SpawnData& data )
	{
		b2BodyDef def;
		def.angle = data.angle;
		def.position = data.position;
		def.linearVelocity = data.velocity;
		def.angularVelocity = data.angular_velocity;
		return def;
	}

	SpawnData& subordinate( SpawnData& data, const IGameObject& parent )
	{
		data.velocity = parent.body().velocity_at( data.position );
		data.position = world_point(parent.body(), data.position );
		data.angle += parent.body().angle();
		return data;
	}

	std::function<void(IGameWorld&, const ISpawnManager&)> make_spawner( SpawnData data )
	{
		return [data](IGameWorld& world, const ISpawnManager& spawner)
			{
				spawner.spawn( world, data );
			};
	}
}
}

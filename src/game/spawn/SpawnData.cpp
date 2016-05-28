#include "SpawnData.h"
#include "game/IGameObject.h"
#include <Box2D/Dynamics/b2Body.h>

namespace game
{
namespace spawn
{
	SpawnData::SpawnData( SpawnType category_, std::string type_, b2Vec2 pos_ ) : 
		category( category_ ),
		type( std::move(type_) ),
		position( std::move(pos_) )
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
		data.velocity = parent.body()->GetWorldVector( data.velocity ) + parent.body()->GetLinearVelocityFromLocalPoint( data.position );
		data.position = parent.body()->GetWorldPoint( data.position );		
		data.angle += parent.body()->GetAngle();
	}
}
}

#ifndef CONVERT_H_INCLUDED
#define CONVERT_H_INCLUDED

class b2Vec2;

namespace game
{
namespace physics
{
	class Body;

	b2Vec2 world_vector( const Body& reference, const b2Vec2& local );
	b2Vec2 local_vector( const Body& reference, const b2Vec2& global );

	b2Vec2 world_point( const Body& reference, const b2Vec2& local );
	b2Vec2 local_point( const Body& reference, const b2Vec2& global );
}
}

#endif // CONVERT_H_INCLUDED

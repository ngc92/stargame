#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

// can we hide these?
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>

#include <boost/variant.hpp>

class b2Shape;

namespace game
{
namespace physics
{
	class Shape
	{
	public:
		typedef boost::variant<b2CircleShape, b2EdgeShape, b2PolygonShape> shape_t;
	public:
		Shape( shape_t shape );
		Shape( const b2Shape& source );
		
		// creator functions
		static Shape circle( float radius, b2Vec2 center = b2Vec2(0, 0) ); 
		static Shape edge( b2Vec2 A, b2Vec2 B ); 
		
		void scale( float factor );
		float getArea() const;
		b2MassData getMassData( float density );
	private:
		shape_t mBoxShape;
		
		friend const b2Shape* to_b2shape(const Shape& shape);
	};
	
	
	const b2Shape* to_b2shape(const Shape& shape);
}
}

#endif // SHAPE_H_INCLUDED

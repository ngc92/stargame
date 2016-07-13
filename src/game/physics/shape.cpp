#include "fixture.h"
#include "shape.h"
#include "consts.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include <iostream>

namespace game
{
namespace physics
{
	Shape::shape_t make_variant( const b2Shape& shape )
	{
		switch(shape.GetType())
		{
		case b2Shape::e_circle:
			return Shape::shape_t( dynamic_cast<const b2CircleShape&>(shape) );
		case b2Shape::e_edge:
			return Shape::shape_t( dynamic_cast<const b2EdgeShape&>(shape) );
		case b2Shape::e_polygon:
			return Shape::shape_t( dynamic_cast<const b2PolygonShape&>(shape) );
		default:
			assert(0);
		}
	}
	
	Shape::Shape( shape_t shape ) : mBoxShape( std::move(shape) )
	{
		
	}

	Shape::Shape( const b2Shape& source ) : mBoxShape( make_variant(source) )
	{
		
	}
		
	Shape Shape::circle( float radius, b2Vec2 center )
	{
		b2CircleShape shape;
		shape.m_radius = radius;
		shape.m_p = center;
		return Shape(std::move(shape));
	}
	
	Shape Shape::edge( b2Vec2 A, b2Vec2 B )
	{
		b2EdgeShape shape;
		shape.Set(A, B);
		return Shape(std::move(shape));
	}
	
	struct ScaleVariant : public boost::static_visitor<void>
	{
		ScaleVariant(float fac) : factor(fac) {}
		float factor;
		void operator()( b2CircleShape& source )
		{
			source.m_p *= factor;
			source.m_radius *= factor;
		}

		void operator()( b2EdgeShape& source )
		{
			source.m_vertex0 *= factor;
			source.m_vertex1 *= factor;
			source.m_vertex2 *= factor;
			source.m_vertex3 *= factor;
		}

		void operator()( b2PolygonShape& source )
		{
			std::array<b2Vec2, b2_maxPolygonVertices> vertices;
			for(int i = 0; i < source.GetVertexCount(); ++i)
			{
				vertices[i] = factor * source.GetVertex(i);
			}

			source.Set( vertices.data(), source.GetVertexCount() );
		}
	};
	
	struct PtrVariant : public boost::static_visitor<const b2Shape*>
	{
		template<class T>
		const b2Shape* operator()( const T& source )
		{
			return &source;
		}
	};
	
	void Shape::scale( float factor )
	{
		ScaleVariant v(factor);
		mBoxShape.apply_visitor(v);
	}
	
	const b2Shape* as_b2shape(const Shape& shape)
	{
		PtrVariant v;
		return shape.mBoxShape.apply_visitor( v );
	}
}
}

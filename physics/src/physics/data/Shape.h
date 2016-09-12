#ifndef DATA_SHAPE_H_INCLUDED
#define DATA_SHAPE_H_INCLUDED

#include "Box2D/Common/b2Math.h"
#include <vector>
#include <iosfwd>

namespace physics
{
	namespace data
	{
		// ---------------------------------------------------------------------------------------------------
		//												Circle Shape
		// ---------------------------------------------------------------------------------------------------
		class CircleShape
		{
		public:
			
			CircleShape( float radius, b2Vec2 center = b2Vec2(0, 0) ) : 
				mCenter(center), mRadius( check_radius(radius) )
			{
			}
			
			// setters
			void setCenter( b2Vec2 c )     { mCenter = c; }
			void setRadius( float radius ) { mRadius = check_radius(radius); }
			
			// getters
			const b2Vec2& center() const   { return mCenter; }
			float radius() const 		   { return mRadius; }
			
		private:
			
			static float check_radius(float radius);
			
			b2Vec2 mCenter;
			float  mRadius;
		};
		
		std::ostream& operator<<(std::ostream& stream, const CircleShape& shape);
		bool operator==( const CircleShape& lhs, const CircleShape& rhs );
		
		// ---------------------------------------------------------------------------------------------------
		//												Polygon Shape
		// ---------------------------------------------------------------------------------------------------
		class PolygonShape
		{
		public:
			PolygonShape( ) = default;
			PolygonShape( std::initializer_list<b2Vec2> data );
			
			// setters
			void setVertices(std::initializer_list<b2Vec2> vtx );
			void setVertices( std::vector<b2Vec2> vtx );
			
			// getters
			std::size_t getVertexCount() const 			{ return mVertices.size(); }
			const std::vector<b2Vec2>& vertices() const { return mVertices; }
			
			bool valid() const;
			
		private:
			
			std::vector<b2Vec2> mVertices;
		};
		
		std::ostream& operator<<( std::ostream& stream, const PolygonShape& shape ); 
		bool operator==( const PolygonShape& lhs, const PolygonShape& rhs );
	}
}

#endif // DATA_SHAPE_H_INCLUDED

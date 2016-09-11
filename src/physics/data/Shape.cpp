#include "Shape.h"
#include <boost/throw_exception.hpp>
#include <stdexcept>
#include <iostream>

namespace physics
{
namespace data
{
	// ---------------------------------------------------------------------------------------------------
	//												Circle Shape
	// ---------------------------------------------------------------------------------------------------
	
	float CircleShape::check_radius(float radius)
	{
		if(radius <= 0)
			BOOST_THROW_EXCEPTION( std::logic_error("Non-positive radius supplied to CircleShape") );
		return radius;
	}
	
	std::ostream& operator<<(std::ostream& stream, const CircleShape& shape)
	{
		/// \todo print center
		return stream << "Circle(" << /* shape.center() <<*/ ", " << shape.radius() << ")";
	}
	
	bool operator==( const CircleShape& lhs, const CircleShape& rhs )
	{
		return lhs.radius() == rhs.radius() && lhs.center() == rhs.center();
	}
	
	// ---------------------------------------------------------------------------------------------------
	//												Polygon Shape
	// ---------------------------------------------------------------------------------------------------
	PolygonShape::PolygonShape( std::initializer_list<b2Vec2> data ) : mVertices( std::move(data) )
	{
		// We could maybe just use a line segment if we get two points.
		// But we require this to be explicit.
		if(mVertices.size() < 3)
			BOOST_THROW_EXCEPTION( std::logic_error("Polygon need to have at least three vertices.") );
		if(mVertices.size() > b2_maxPolygonVertices)
			BOOST_THROW_EXCEPTION( std::logic_error("Box2D supports at most b2_maxPolygonVertices vertices.") );
	} 
	
	// setters
	void PolygonShape::setVertices(std::initializer_list<b2Vec2> vtx )
	{
		mVertices = std::move(vtx);
		if(mVertices.size() < 3)
			BOOST_THROW_EXCEPTION( std::logic_error("Polygon need to have at least three vertices.") );
		if(mVertices.size() > b2_maxPolygonVertices)
			BOOST_THROW_EXCEPTION( std::logic_error("Box2D supports at most b2_maxPolygonVertices vertices.") );
	}
	
	void PolygonShape::setVertices( std::vector<b2Vec2> vtx )
	{
        mVertices = std::move(vtx);
		if(mVertices.size() < 3)
			BOOST_THROW_EXCEPTION( std::logic_error("Polygon need to have at least three vertices.") );
		if(mVertices.size() > b2_maxPolygonVertices)
			BOOST_THROW_EXCEPTION( std::logic_error("Box2D supports at most b2_maxPolygonVertices vertices.") );
	}
	
	bool PolygonShape::valid() const 
	{ 
		return  mVertices.size() >= 3 && 
				mVertices.size() <= b2_maxPolygonVertices; 
	}
	
	std::ostream& operator<<( std::ostream& stream, const PolygonShape& shape )
	{
		/// \todo print vertices
		return stream << "Polygon()";
	}
	
	bool operator==( const PolygonShape& lhs, const PolygonShape& rhs )
	{
		if(lhs.getVertexCount() != rhs.getVertexCount())
			return false;
		return std::equal( begin(lhs.vertices()), end(lhs.vertices()), begin(rhs.vertices()) );
	}
}
}

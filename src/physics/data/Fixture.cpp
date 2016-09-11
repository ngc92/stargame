#include "Fixture.h"
#include <boost/throw_exception.hpp>
#include <stdexcept>

namespace physics
{
namespace data
{
	Fixture::Fixture( shape_t shape ) :
		mShape( std::move(shape) ) 
	{
		if(mShape.type() == typeid(PolygonShape))
		{
			if(!boost::get<PolygonShape>(mShape).valid())
				BOOST_THROW_EXCEPTION( std::logic_error("Invalid polygon supplied as shape.") );
		}
	}
	
	
	Fixture& Fixture::setFriction( float f )
	{
		if(f < 0)
			BOOST_THROW_EXCEPTION( std::domain_error("Friction cannot be negative.") );
		mFriction = f;
		return *this;
	}
	
	Fixture& Fixture::setRestitution( float r )
	{
		if(r < 0)
			BOOST_THROW_EXCEPTION( std::domain_error("Restitution cannot be negative.") );
		mRestitution = r;
		return *this;
	}
	
	Fixture& Fixture::setDensity( float d )
	{
		if(d < 0)
			BOOST_THROW_EXCEPTION( std::domain_error("Density cannot be negative.") );
		mDensity = d;
		return *this;
	}
	
	Fixture& Fixture::setSensor( bool s )
	{
		mIsSensor = s;
		return *this;
	}
	
	Fixture& Fixture::setShape( shape_t shape )
	{
		if(shape.type() == typeid(PolygonShape))
		{
			if(!boost::get<PolygonShape>(shape).valid())
				BOOST_THROW_EXCEPTION( std::logic_error("Invalid polygon supplied as shape.") );
		}
		mShape = std::move(shape);
		return *this;
	}
}
}

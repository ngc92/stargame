#include "Body.h"
#include <stdexcept>
#include <boost/throw_exception.hpp>

namespace physics
{
namespace data
{
	BodyDef& BodyDef::setLinearDamping(  float d ) 
	{
		if( d < 0 )
			BOOST_THROW_EXCEPTION( std::domain_error("Negative damping supplied to BodyDef.") );
		mLinearDamping = d;  
		return *this; 
	}
	
	BodyDef& BodyDef::setAngularDamping( float d ) 
	{ 
		if( d < 0 )
			BOOST_THROW_EXCEPTION( std::domain_error("Negative damping supplied to BodyDef.") );
		mAngularDamping = d; 
		return *this; 
	}
	
	BodyDef& BodyDef::setFixedRotation( bool f )   { mFixedRotation = f;  return *this; }
	BodyDef& BodyDef::setBullet( bool b )          { mBullet = b;         return *this; }
}
}

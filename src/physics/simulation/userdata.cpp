#include "userdata.h"
#include <Box2D/Dynamics/b2Body.h>
#include <boost/throw_exception.hpp>

namespace physics
{
namespace simulation
{
	const BodyUserData& get_userdata( const b2Body& body )
	{
		auto ptr = reinterpret_cast<const BodyUserData*>(body.GetUserData());
		if(!ptr)
			BOOST_THROW_EXCEPTION( std::logic_error("No user pointer set in body.") );
		return *ptr;
	}
	
}
}

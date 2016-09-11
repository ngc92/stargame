#ifndef USERDATA_H_INCLUDED
#define USERDATA_H_INCLUDED

#include <cstdint>

class b2Body;

namespace physics
{
namespace simulation
{
	struct BodyUserData
	{
		uint64_t id;
	};
	
	const BodyUserData& get_userdata( const b2Body& body );
}
}

#endif // USERDATA_H_INCLUDED

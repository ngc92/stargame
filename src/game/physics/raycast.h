#ifndef RAYCAST_H_INCLUDED
#define RAYCAST_H_INCLUDED

class b2RayCastInput;
class b2RayCastOutput;
class b2Transform;

namespace game
{
namespace physics
{
	class Shape;
	
	bool raycast(b2RayCastOutput& out, const Shape& shape, const b2RayCastInput& in, const b2Transform& transform);
}
}

#endif // RAYCAST_H_INCLUDED

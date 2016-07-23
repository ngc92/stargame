#include "raycast.h"
#include "shape.h"
#include <Box2D/Collision/Shapes/b2Shape.h>

namespace game
{
namespace physics
{
	bool raycast(b2RayCastOutput& out, const Shape& shape, const b2RayCastInput& in, const b2Transform& transform)
	{
		return as_b2shape(shape)->RayCast(&out, in, transform, 0);
	}
}
}

#include <Box2D/Common/b2Math.h>
#include <irrlicht/vector3d.h>

const double FACTOR = 40;

inline irr::core::vector3df b2i(b2Vec2 v)
{
	return irr::core::vector3df( -v.x * FACTOR, 0, v.y * FACTOR );
}

inline b2Vec2 i2b(irr::core::vector3df v)
{
	return b2Vec2( -v.X / FACTOR, v.Z / FACTOR );
}

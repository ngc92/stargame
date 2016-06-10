#include <Box2D/Common/b2Math.h>
#include <irrlicht/vector3d.h>

inline irr::core::vector3df b2i(b2Vec2 v)
{
	return irr::core::vector3df( v.x, 0, v.y );
}

inline b2Vec2 i2b(irr::core::vector3df v)
{
	return b2Vec2( v.X, v.Z );
}

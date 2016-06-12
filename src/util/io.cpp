#include "io.h"
#include <iostream>
#include <Box2D/Common/b2Math.h>

std::ostream& operator<<(std::ostream& out, b2Vec2 v)
{
	return out << "(" << v.x << ", " << v.y << ")";
}

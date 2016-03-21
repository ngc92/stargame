#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <memory>
#include <Box2D/Common/b2Math.h>
#include <irrlicht/vector2d.h>
#include <boost/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include "util/make_unique.h"
#include "util/ObjectCounter.h"

// forward declarations
class b2Body;
class b2World;

namespace irr
{
	class IrrlichtDevice;
	namespace video
	{
		class SColor;
		class ITexture;
	}
}

typedef b2Body PhysicsLibraryBodyType;
typedef b2World PhysicsLibraryWorldType;
typedef irr::IrrlichtDevice DeviceType;

typedef irr::video::SColor color_type;
typedef b2Vec2 vector2d;
typedef irr::core::vector2di screen_vector;
typedef irr::video::ITexture texture_type;
// can't forward declare screen_vector, as it is a template typedef

#define __unused __attribute__((unused))

using boost::noncopyable;

template<class T>
std::string to_string(const T& t)
{
	return boost::lexical_cast<std::string>(t);
}

#endif // UTIL_H_INCLUDED

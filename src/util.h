#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <memory>
#include <Box2D/Common/b2Math.h>

#include <irrlicht/vector2d.h>
#include <irrlicht/SColor.h>

#include <boost/noncopyable.hpp>
#include <boost/lexical_cast.hpp>

#include "util/make_unique.h"
#include "util/logging.h"
#include "util/convert.h"
#include "debug/ObjectCounter.h"

// forward declarations
class b2Body;
class b2World;
class b2Fixture;

namespace irr
{
	class IrrlichtDevice;
	namespace video
	{
		class ITexture;
	}
	namespace io
	{
		class IAttributes;
	}
	namespace gui
	{
		class IGUIEnvironment;
		class IGUIElement;
	}
}

typedef irr::IrrlichtDevice DeviceType;
using irr::gui::IGUIEnvironment;
using irr::gui::IGUIElement;

typedef irr::video::SColor color_type;
typedef b2Vec2 vector2d;
typedef irr::core::vector2di screen_vector;
typedef irr::video::ITexture texture_type;

/// use this as default argument for color multiplying modifications. White with full alpha -> no change
const color_type ColorWhite = color_type(255, 255, 255, 255);

#define __unused __attribute__((unused))

using boost::noncopyable;

template<class T>
std::string to_string(const T& t)
{
	return boost::lexical_cast<std::string>(t);
}

template<class... Args>
class ListenerList;

class ListenerRef;

#endif // UTIL_H_INCLUDED

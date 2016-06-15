#ifndef MICRO_BEHAVIOUR_H_INCLUDED
#define MICRO_BEHAVIOUR_H_INCLUDED

#include <Box2D/Common/b2Math.h>
#include <boost/optional.hpp>
#include <boost/variant.hpp>
#include <vector>

namespace game
{
class IGameObject;
namespace ai
{
	class Control;

	struct ShipInfo
	{
		// cached info about our ship
		float mMaxVelocity = 0;
		float mMaxThrust = 0;
		float mMaxTorque = 0;
	};

	namespace micro_behaviours
	{
		//! \brief Move to desired position.
		struct MoveTo{ b2Vec2 target; };
		struct Face{ b2Vec2 target; };

		using behaviour_t = boost::variant<MoveTo, Face>;

		Control apply( const behaviour_t& behaviour, const IGameObject& object, const ShipInfo& info  );
	}

	using micro_behaviours::behaviour_t;

}
}

#endif // MICRO_BEHAVIOUR_H_INCLUDED

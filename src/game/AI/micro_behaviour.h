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
	namespace micro_behaviours
	{
		//! \brief Move to desired position.
		struct MoveTo{ b2Vec2 target; };
		struct Face{ b2Vec2 target; };

		using behaviour_t = boost::variant<MoveTo, Face>;
	}

	struct ShipInfo
	{
		ShipInfo(IGameObject& ship);
		// cached info about our ship
		float mMaxVelocity = 0;
		float mMaxThrust = 0;
		float mMaxTorque = 0;
	};

	class MicroBehaviour
	{
	public:
		MicroBehaviour( IGameObject& target );
		~MicroBehaviour() = default;

		// setting the current behaviour
		void move_to(b2Vec2 pos);
		void face( b2Vec2 pos );

		/// \todo the current design does not allow us to specifiy that object as such should remain const,
		///			but its inputs should change. Can we do sth. smart about that?
		void act( IGameObject& object );

		void updateShipInfo(IGameObject& ship);
	private:

		micro_behaviours::behaviour_t mCurrentBehaviour;

		ShipInfo mInfo;
	};
}
}

#endif // MICRO_BEHAVIOUR_H_INCLUDED

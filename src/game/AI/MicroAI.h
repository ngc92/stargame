#ifndef MICROAI_H_INCLUDED
#define MICROAI_H_INCLUDED

#include <memory>
#include <vector>

#include "micro_behaviour.h"
#include "IAIRegistrator.h"

namespace game
{
class IGameObject;
namespace ai
{
	class IPropulsionSystem;
	class ShipInfo;

	class MicroAI : public IAIRegistrator
	{
		class Registrator;
	public:
		MicroAI( );
		~MicroAI();

		void act( const IGameObject& object );

		// registration/removal of prop sys
		std::shared_ptr<void> registerPropulsionSystem( IPropulsionSystem& propsys ) override;
		void removePropulsionSystem( IPropulsionSystem& propsys );

		void move_to(b2Vec2 pos);

	private:
		std::vector<IPropulsionSystem*> mPropulsionSystems;
		std::shared_ptr<Registrator> mRegistrator;

		std::unique_ptr<ShipInfo> mShipInfo;

		bool mActive = false;
		behaviour_t mCurrentBehaviour;

	};
}
}
#endif // MICROAI_H_INCLUDED

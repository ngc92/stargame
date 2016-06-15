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
		MicroAI(MicroAI&&) = default;

		void act( const IGameObject& object );

		// registration/removal of prop sys
		std::shared_ptr<void> registerPropulsionSystem( IPropulsionSystem& propsys ) override;
		std::shared_ptr<void> registerWeaponSystem( IWeaponSystem& propsys ) override;
		void removeSystem( IPropulsionSystem& propsys );
		void removeSystem( IWeaponSystem& propsys );

		void move_to(b2Vec2 pos);

	private:
		std::vector<IPropulsionSystem*> mPropulsionSystems;
		std::vector<IWeaponSystem*> mWeaponSystems;
		std::shared_ptr<Registrator> mRegistrator;

		std::unique_ptr<ShipInfo> mShipInfo;

		std::vector<behaviour_t> mCurrentBehaviours;

	};
}
}
#endif // MICROAI_H_INCLUDED

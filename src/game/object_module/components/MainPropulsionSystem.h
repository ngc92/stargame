#ifndef MAINPROPULSIONSYSTEM_H_INCLUDED
#define MAINPROPULSIONSYSTEM_H_INCLUDED

#include "CComponent.h"
#include "input/IInputElement.h"
#include "game/ai/IPropulsionSystem.h"

namespace game
{
class IFlightModel;
namespace components
{
	class MainPropulsionSystem : public CComponent, public ai::IPropulsionSystem
	{
		public:
			MainPropulsionSystem();
			virtual ~MainPropulsionSystem();

			void init(IGameObject& object) override;
			void step(IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action) override;

			// propulsion system interface
			float getMaxTorque() const override;
			float getMaxThrust() const override;
			float check_rotate( float rot ) const override;
			b2Vec2 check_thrust( const b2Vec2& thrust ) const override;

			// action functions
			void rotate(float rot) override;
			void thrust(const b2Vec2& thr) override;

		private:
			std::weak_ptr<IComponent> mTank;
			std::shared_ptr<IFlightModel> mFlightModel;
			std::shared_ptr<void> mFlightRegistration; //!< this variable contains just a d'tor to unregister

			// properties
			Property<float> mThrust;
			Property<float> mFuelEfficiency;
			/// \todo do we want engine overheating?

			// controls
			Property<float> mThrustLevel;
			Property<float> mAfterburner;
	};
}
}


#endif // MAINPROPULSIONSYSTEM_H_INCLUDED

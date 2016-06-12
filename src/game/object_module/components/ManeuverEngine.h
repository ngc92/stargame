#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "CComponent.h"
#include "input/IInputElement.h"
#include "game/object_module/IPropulsionSystem.h"

namespace game
{
	class IFlightModel;
namespace components
{
	//! \todo Möglichkeit Einbauen, evtl. einen zweiten Tank zu nutzen usw
	class ManeuverEngine : public CComponent, public IPropulsionSystem
	{
		public:
			ManeuverEngine();
			virtual ~ManeuverEngine();

			// component interface
			void init(IGameObject& object) override;
			void step(IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action) override;

			// info functions
			float getMaxTorque() const override;
			float getMaxThrust() const override;

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
			Property<float> mTorque;
			/// \todo do we want engine overheating?

			// controls
			Property<float> mLateralControl;
			Property<float> mLongitudinalControl;
			Property<float> mTurnControl;
	};
}
}
#endif // ENGINE_H_INCLUDED

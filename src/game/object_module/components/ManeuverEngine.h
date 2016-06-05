#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "CComponent.h"
#include "input/IInputElement.h"

namespace game
{
	class IFlightModel;
namespace components
{
	//! \todo Möglichkeit Einbauen, evtl. einen zweiten Tank zu nutzen usw
	class ManeuverEngine : public CComponent
	{
		public:
			ManeuverEngine();
			virtual ~ManeuverEngine();

			void init(IGameObject& object) override;
			void step(IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action) override;

		private:
			std::weak_ptr<IComponent> mTank;
			std::shared_ptr<IFlightModel> mFlightModel;

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

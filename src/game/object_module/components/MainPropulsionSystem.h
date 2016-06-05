#ifndef MAINPROPULSIONSYSTEM_H_INCLUDED
#define MAINPROPULSIONSYSTEM_H_INCLUDED

#include "CComponent.h"
#include "input/IInputElement.h"

namespace game
{
class IFlightModel;
namespace components
{
	//! \todo Möglichkeit Einbauen, evtl. einen zweiten Tank zu nutzen usw
	class MainPropulsionSystem : public CComponent
	{
		public:
			MainPropulsionSystem();
			virtual ~MainPropulsionSystem();

			void init(IGameObject& object) override;
			void step(IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action) override;

		private:
			std::weak_ptr<IComponent> mTank;
			std::shared_ptr<IFlightModel> mFlightModel;

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

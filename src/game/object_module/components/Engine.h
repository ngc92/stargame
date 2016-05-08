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
	class Engine : public CComponent
	{
		public:
			Engine();
			virtual ~Engine();

			void init(IGameObject& object) override;
			void step() override;

		private:
			std::weak_ptr<IComponent> mTank;
			std::shared_ptr<IFlightModel> mFlightModel;

			// properties
			Property<float> mThrust;
			Property<float> mFuelEfficiency;
			Property<float> mTorque;
			/// \todo do we want engine overheating?

			// controls
			Property<float> mThrustLevel;
			Property<float> mTurnControl;
			Property<float> mAfterburner;
	};
}
}
#endif // ENGINE_H_INCLUDED

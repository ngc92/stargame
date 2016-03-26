#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "CComponent.h"
#include "input/IInputElement.h"

namespace game
{
namespace components
{
	//! \todo Möglichkeit Einbauen, evtl. einen zweiten Tank zu nutzen usw
	class Engine : public CComponent
	{
		public:
			Engine();
			virtual ~Engine();

			void init(IActionListInterface& actionlist, input::IInputCollection& inputs) override;
			void step(IActionListInterface& actionlist) override;

			// supply interface
			void registerSupplier(const std::string& resource, IComponent* component) override;

		private:
			IComponent* mTank = nullptr;

			// properties
			Property<float> mThrust;
			Property<float> mFuelConsumption;

			// controls
			std::shared_ptr<input::IInputElement> mThrustLevel;
	};
}
}
#endif // ENGINE_H_INCLUDED

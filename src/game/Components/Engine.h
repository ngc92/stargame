#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED

#include "CComponent.h"

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

			void init(IActionListInterface& actionlist) override;
			void step(IActionListInterface& actionlist) override;

			// supply interface
			void registerSupplier(const std::string& resource, IComponent* component) override;

		private:
			IComponent* mTank = nullptr;
	};
}
}
#endif // ENGINE_H_INCLUDED

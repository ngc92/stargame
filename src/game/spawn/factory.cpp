#include "factory.h"
#include "util.h"

#include "game/object_module/components/FuelTank.h"
#include "game/object_module/components/Engine.h"
#include "game/object_module/components/CargoBay.h"
#include "game/object_module/components/FixedGun.h"

#include "game/object_module/CStructureCell.h"
#include "game/object_module/CSubStructure.h"

#include "Definitions.h"

#include <Box2D/Collision/Shapes/b2Shape.h>

namespace game
{
namespace spawn
{

	std::shared_ptr<IComponent> constructComponent(const std::string& type)
	{
		/// \todo replace with factory interface
		if(type == "FuelTank")
		{
			return std::make_shared<components::FuelTank>();
		}
		else if(type == "Engine")
		{
			return std::make_shared<components::Engine>();
		}
		else if(type == "CargoBay")
		{
			return std::make_shared<components::CargoBay>();
		}
		else if(type == "FixedGun")
		{
			return std::make_shared<components::FixedGun>();
		}
		assert(0);
	}

	std::unique_ptr<IStructureCell> createStructureCell( long id, float maxload, std::unique_ptr<b2Shape> shape)
	{
		return make_unique<CStructureCell>(id, maxload, std::move(shape));
	}

	std::shared_ptr<ISubStructure> createSubStructure()
	{
		return std::make_shared<CSubStructure>();
	}
}
}

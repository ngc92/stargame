#ifndef COMPONENT_FACTORY_H_INCLUDED
#define COMPONENT_FACTORY_H_INCLUDED

#include <memory>
#include "game/fwd.h"

class b2Shape;

namespace game
{
	class IStructureCell;

	namespace spawn
	{
		std::shared_ptr<IComponent> constructComponent(const std::string& type);
		std::unique_ptr<IStructureCell> createStructureCell( long id, float maxload, std::unique_ptr<b2Shape> shape);
		std::shared_ptr<ISubStructure> createSubStructure();
	}
}

#endif // COMPONENT_FACTORY_H_INCLUDED

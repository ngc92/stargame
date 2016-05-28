#ifndef ISPAWNMANAGER_H_INCLUDED
#define ISPAWNMANAGER_H_INCLUDED

#include <memory>
#include <string>
#include "game/fwd.h"

namespace game
{	
class IGameWorld;
	
namespace spawn
{
	class SpawnData;
	
	class ISpawnManager
	{
	public:		
		ISpawnManager() = default;

		virtual ~ISpawnManager() = default;

		virtual std::shared_ptr<IGameObject> spawn( IGameWorld& world, const spawn::SpawnData& data ) const = 0;
	};
}
}

#endif // ISPAWNMANAGER_H_INCLUDED

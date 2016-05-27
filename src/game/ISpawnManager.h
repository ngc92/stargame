#ifndef ISPAWNMANAGER_H_INCLUDED
#define ISPAWNMANAGER_H_INCLUDED

#include <memory>
#include <string>
#include "fwd.h"
#include <Box2D/Common/b2Math.h>

class b2Body;

namespace game
{	
	namespace spawn
	{
		class SpawnData;
	}
	
	class ISpawnManager
	{
	public:		
		ISpawnManager()
		{
			assert( mSingleton == nullptr );
			mSingleton = this;
		}

		virtual ~ISpawnManager()
		{
			mSingleton = nullptr;
		}

		static ISpawnManager& singleton() { return *mSingleton; }
		
		virtual std::shared_ptr<IGameObject> spawn( IGameWorld& world, const spawn::SpawnData& data ) = 0;
	private:

		static ISpawnManager* mSingleton;
	};
}

#endif // ISPAWNMANAGER_H_INCLUDED

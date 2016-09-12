#include "CSimulationWorld.h"
#include "../IGameObject.h"
#include "../spawn/ISpawnManager.h"
#include "../IGameViewModule.h"
#include "util/algos.h"
#include <iostream>
#include "physics/IPhysicsThread.h"

namespace game
{
	CSimulationWorld::CSimulationWorld()
	{
/*		getWorld().SetContactFilter( mContactListener.get() );
*/
	}

	CSimulationWorld::~CSimulationWorld()
	{
	}

	void CSimulationWorld::step(const spawn::ISpawnManager& spawner)
	{
		mPhysics->updateEvents();
		const auto& events = mPhysics->getEvents();
		
		// update all current objects and remove old ones.
		update_game_objects(spawner);
		notify_game_objects( );

		// spawn new objects
		perform_spawning();

		// finally, update all modules
		for(auto& mod : mModules)
		{
			auto locked = mod.lock();
			if(locked)
			{
				locked->step( *this, spawner );
			}
		}

		remove_expired(mModules);

		update_view_modules();
	}

	void CSimulationWorld::addModule(std::weak_ptr<IGameModule> module)
	{
		auto locked = module.lock();
		if(locked)
		{
			locked->init( *this );
			mModules.push_back( std::move(module) );
		}
	}

	// -----------------------------------------------------------
	//			constructor function
	// -----------------------------------------------------------
	std::unique_ptr<IGameWorld> createSimulationWorld()
	{
		return std::make_unique<CSimulationWorld>();
	}
}

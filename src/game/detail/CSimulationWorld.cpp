#include "CSimulationWorld.h"
#include "../IGameObject.h"
#include "../spawn/ISpawnManager.h"
#include "../IGameViewModule.h"
#include "../physics/ContactListener.h"
#include "util/algos.h"
#include <Box2D/Dynamics/b2World.h>
#include <iostream>

namespace game
{
	CSimulationWorld::CSimulationWorld() : mContactListener( std::make_unique<physics::ContactListener>() )
	{
		getWorld().SetContactListener( mContactListener.get() );
		getWorld().SetContactFilter( mContactListener.get() );
	}

	CSimulationWorld::~CSimulationWorld()
	{
	}

	void CSimulationWorld::step(const spawn::ISpawnManager& spawner)
	{
		// do actually 2 physic steps per loop step.
		// this makes it possible for bodies to move faster.
		constexpr const int SUB_STEPS = 2;
		// step the physic world
		for(int i = 0; i < SUB_STEPS; ++i)
		{
			getWorld().Step(1.0/60 / SUB_STEPS, 8, 3);
			// and trigger corresponding physic events
			mContactListener->triggerEvents();
		}
		getWorld().ClearForces();
		
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

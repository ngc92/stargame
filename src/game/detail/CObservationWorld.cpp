#include "CObservationWorld.h"
#include "../IGameObject.h"
#include "../spawn/ISpawnManager.h"
#include "../IGameViewModule.h"
#include "../physics/ContactListener.h"
#include "util/algos.h"
#include <Box2D/Dynamics/b2World.h>
#include <iostream>

namespace game
{
	CObservationWorld::CObservationWorld() : mContactListener( std::make_unique<ContactListener>() )
	{
		getWorld().SetContactFilter( mContactListener.get() );
	}

	CObservationWorld::~CObservationWorld()
	{
	}

	void CObservationWorld::step(const spawn::ISpawnManager& spawner)
	{
		
		/// \todo do some physics simulation, i.e. just propagate positions according to passed time.
		
		// update all current objects and remove old ones.
		update_game_objects(spawner);

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

	void CObservationWorld::addModule(std::weak_ptr<IGameModule> module)
	{
		auto locked = module.lock();
		if(locked)
		{
			locked->init( *this );
			mModules.push_back( std::move(module) );
		}
	}
}

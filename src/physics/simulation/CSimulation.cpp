#include "CSimulation.h"
#include "ISpawner.h"
#include "physics/events/SpawnEvent.h"
#include <iostream>

namespace physics
{
namespace simulation
{
	CSimulation::CSimulation(std::unique_ptr<ISpawner> spawner, std::shared_ptr<ISimulationEventListener> listener) : 
		mWorld( b2Vec2(0,0) ),
		mSpawner( std::move(spawner) ),
		mListener( std::move(listener) )
	{
		
	}
	
	CSimulation::~CSimulation()
	{
	}
	
	std::size_t CSimulation::getBodyCount() const
	{
		return mWorld.GetBodyCount();
	}
	
	void CSimulation::step( double dt )
	{
		mPartialStep += dt;
		
		while(mPartialStep >= mStepSize)
		{
			tick();
			mPartialStep -= mStepSize;
		}
		
		// generate object state updates
		auto body = mWorld.GetBodyList();
		while(body)
		{
			events::ObjectStateUpdateEvent update;
//			update.object_id    = ;
			update.position     = body->GetPosition();
			update.velocity     = body->GetLinearVelocity();
			update.rotation     = body->GetAngle();
			update.ang_velocity = body->GetAngularVelocity();
			
			if(mListener)
				mListener->onObjectStateUpdate( update );
			
			body = body->GetNext();
		}
	}
	
	void CSimulation::spawn( const actions::SpawnObject& spw )
	{
		auto body = mSpawner->spawnBody( mWorld, spw.body );
		for(const auto& fix : spw.fixtures)
		{
			mSpawner->spawnFixture( *body, fix );
		}
		
		// trigger spawn event!
		events::SpawnEvent spawn{0, spw.body};
		if(mListener)
			mListener->onSpawn( spawn );
	}
	
	void CSimulation::tick()
	{
		mWorld.Step(mStepSize, 8, 3);
		// and trigger corresponding physic events
		//mContactListener->triggerEvents();
	}
}
}

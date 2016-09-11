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
		mListener( std::move(listener) ),
		mConverter(1.0)
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
			update.object_id    = get_userdata(*body).id;
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
		auto body = mSpawner->spawnBody( mWorld, mConverter.toBoxUnits(spw.body) );
		// add user pointer to body.
		mUserData.push_back( std::unique_ptr<BodyUserData>( new BodyUserData ) );
		mUserData.back()->id = ++next_id;
		body->SetUserData( mUserData.back().get() );
		
		for(const auto& fix : spw.fixtures)
		{
			mSpawner->spawnFixture( *body, mConverter.toBoxUnits(fix) );
		}
		
		// trigger spawn event!
		events::SpawnEvent spawn{mUserData.back()->id, spw.body};
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

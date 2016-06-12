#include "CTimedDeletion.h"

namespace game
{
	CTimedDeletion::CTimedDeletion( int lifetime ):
		CPropertyObject( "timed_deletion" ),
		mElapsedLifetime( "age", this, 0),
		mTotalLifetime( "lifetime", this, lifetime )
	{

	}

	/// gets the scheduled time of deletion
	int CTimedDeletion::getTotalLifetime() const
	{
		return mTotalLifetime;
	}

	/// gets the time of creation (of this timer)
	int CTimedDeletion::getElapsedLifetime() const
	{
		return mElapsedLifetime;
	}

	/// sets the time for scheduled deletion
	void CTimedDeletion::setTotalLifetime( int dur )
	{
		mTotalLifetime = dur;
	}

	/// initialise the module with the object.
	void CTimedDeletion::onInit( IGameObject& object, IGameWorld& world )
	{
		mElapsedLifetime = 0;
	}

	/// this function will be called every step by the game world, and should trigger
	/// the onStep listener.
	void CTimedDeletion::onStep( IGameObject& object, const IGameWorld& world, WorldActionQueue& p)
	{
		mElapsedLifetime = mElapsedLifetime + 1;
		if( mElapsedLifetime > mTotalLifetime )
		{
			object.remove();
		}
	}
}

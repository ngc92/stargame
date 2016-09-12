#include "ContactFilter.h"
#include "game/IGameObject.h" // needed for automatic conversion IGameObjectView* -> IGameObject*

namespace game
{
namespace physics
{
	/*bool ContactFilter::doesCollide(const Body& target) const
	{
		if(mCollisionBlacklist.empty())
			return true;
		
		// if not in blacklist (count == 0), do collide
		return mCollisionBlacklist.count(target.getGameObject()) == 0;
	}
	
	void ContactFilter::addToBlacklist( const IGameObjectView* blacklisted )
	{
		mCollisionBlacklist.insert( blacklisted );
	}
	
	void ContactFilter::removeFromBlacklist( const IGameObjectView* query )
	{
		mCollisionBlacklist.erase( query );
	}*/
}
}

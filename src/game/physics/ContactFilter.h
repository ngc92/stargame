#ifndef CONTACTFILTER_H_INCLUDED
#define CONTACTFILTER_H_INCLUDED

#include <set>

namespace game 
{
class IGameObjectView;
namespace physics
{
	class Body;
	class ContactFilter
	{
	public:
		bool doesCollide(const Body& target) const;
		
		// blacklist management
		void addToBlacklist( const IGameObjectView* blacklisted );
		void removeFromBlacklist( const IGameObjectView* query );
	private:
		/// objects with which this thing does not collide
		std::set<const IGameObjectView*> mCollisionBlacklist; 
	};
}
}

#endif // CONTACTFILTER_H_INCLUDED

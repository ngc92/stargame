#include "CAffiliation.h"

namespace game
{
	CAffiliation::CAffiliation( int team, std::shared_ptr<IGameObjectView> owner ) :
		CPropertyObject("affiliation"),
		mTeam("team", this, team), mOwner( std::move(owner) )
	{
	}

	int _getTeam(const std::shared_ptr<IGameObjectView>& owner)
	{
		auto& prop = owner->getProperty("affiliation.team");
		return boost::get<int>(prop.value());
	}

	CAffiliation::CAffiliation( std::shared_ptr<IGameObjectView> owner ) :
		CAffiliation( _getTeam( owner ), owner /* can't move here, as evaluation order of args is not specified */ )
	{

	}

	int CAffiliation::getTeam() const
	{
		return mTeam;
	}

	const std::shared_ptr<IGameObjectView>& CAffiliation::getOwner() const
	{
		return mOwner;
	}
}

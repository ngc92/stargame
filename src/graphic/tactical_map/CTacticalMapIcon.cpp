#include "CTacticalMapIcon.h"

namespace graphic 
{
namespace detail 
{
	CTacticalMapIcon::CTacticalMapIcon(int team, std::string type, b2Vec2 pos, float angle) :
		mPosition( std::move(pos) ), mAngle( angle ), mTeam( team ), mType( std::move(type) ) 
	{
		
	}

	int CTacticalMapIcon::team() const
	{
		return mTeam;
	}

	const std::string& CTacticalMapIcon::type() const
	{
		return mType;
	}

	const b2Vec2& CTacticalMapIcon::position() const
	{
		return mPosition;
	}

	void CTacticalMapIcon::setPosition(const b2Vec2& pos)
	{
		mPosition = pos;
	}

	float CTacticalMapIcon::angle() const
	{
		return mAngle;
	}

	void CTacticalMapIcon::setAngle(float ang)
	{
		mAngle = ang;
	}
}
}

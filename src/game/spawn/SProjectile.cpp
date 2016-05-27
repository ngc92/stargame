#include "SProjectile.h"
#include "spawn_util.h"

#include "consts.h"

namespace game
{
namespace spawn
{
	SProjectile::SProjectile(const boost::property_tree::ptree& props):
		mName( props.get<std::string>("name") ),
		mPropellantVelocity( props.get<float>("velocity") ),
		mRadius( props.get<float>("radius") / 1000.f ),
		mMass( props.get<float>("mass") ),
		mLifetime( int(props.get<float>("lifetime") * STEPS_PER_SECOND) )
	{

	}

	const std::string& SProjectile::name() const
	{
		return mName;
	}

	float SProjectile::propellVelocity() const
	{
		return mPropellantVelocity;
	}

	float SProjectile::radius() const
	{
		return mRadius;
	}

	float SProjectile::mass() const
	{
		return mMass;
	}

	int SProjectile::lifetime() const
	{
		return mLifetime;
	}
}
}

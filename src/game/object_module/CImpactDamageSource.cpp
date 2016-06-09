#include "CImpactDamageSource.h"
#include "game/Damage.h"

namespace game
{
	CImpactDamageSource::CImpactDamageSource( float damage_factor, float blunt_factor ):
		CPropertyObject("DamageSource"),
		mImpulseFactor( damage_factor ), mBluntFactor( blunt_factor )
	{

	}

	/// this function is called whenever another game object hits the current one.
	void CImpactDamageSource::onImpact( IGameObject& object, IGameObject& other, const ImpactInfo& info)
	{
		float imp = info.impulse * mImpulseFactor;
		Damage d;
		d.setDamage(DamageType::BLUNT, imp * mBluntFactor);
		d.setDamage(DamageType::PIERCE, imp * 1 - mBluntFactor);
		other.dealDamage( d, info.position, info.normal );
	}
}

#ifndef CIMPACTDAMAGESOURCE_H_INCLUDED
#define CIMPACTDAMAGESOURCE_H_INCLUDED

#include "IDamageSource.h"
#include "property/CPropertyObject.h"

namespace game
{
	class CImpactDamageSource : public IDamageSource, public property::CPropertyObject
	{
	public:
		CImpactDamageSource( float damage_factor = 0.5, float blunt_factor = 0.5 );

		void onInit( IGameObject& object, IGameWorld& world ) override {};
		void onStep( IGameObject& object, IGameWorld& world)  override {};

		/// this function is called whenever another game object hits the current one.
		void onImpact( IGameObject& object, IGameObject& other, const ImpactInfo& info) override;
	private:
		float mImpulseFactor = 0.5;
		float mBluntFactor = 0.5;
	};
}

#endif // CIMPACTDAMAGESOURCE_H_INCLUDED

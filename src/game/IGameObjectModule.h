#ifndef IGAMEOBJECTMODULE_H_INCLUDED
#define IGAMEOBJECTMODULE_H_INCLUDED

#include "property/IPropertyObject.h"
#include "IGameObjectView.h"

namespace game
{
	class IGameObject;
	class Damage;

	class IGameObjectModule : public virtual property::IPropertyObject
	{
	public:
		virtual ~IGameObjectModule() = default;

		/// initialise the module with the object.
		virtual void onInit( IGameObject& object, IGameWorld& world ) = 0;

		/// this function will be called every step by the game world, and should trigger
		/// the onStep listener.
		virtual void onStep( IGameObject& object, IGameWorld& world) = 0;

		/// this function is called whenever another game object hits the current one.
		virtual void onImpact( IGameObject& object, IGameObject& other, const ImpactInfo& info) {};

		/*! this function is called when damage is dealt to the object.
			\param object The game object that was damaged.
			\param damage The amount of damage dealt.
			\param pos world position where the damage occured.
			\param dir direction in which the damage is to be applied in world coordinates.
		*/
		virtual void onDamage( IGameObject& object, const Damage& damage, const b2Vec2& pos, const b2Vec2& dir ) {};
	};
}

#endif // IGAMEOBJECTMODULE_H_INCLUDED

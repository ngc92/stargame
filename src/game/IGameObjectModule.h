#ifndef IGAMEOBJECTMODULE_H_INCLUDED
#define IGAMEOBJECTMODULE_H_INCLUDED

#include "property/IPropertyObject.h"
#include "IGameObjectView.h"

namespace game
{
	class IGameObject;

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
		virtual void onImpact( IGameObject& object, IGameObject* other, const ImpactInfo& info) {};
	};
}

#endif // IGAMEOBJECTMODULE_H_INCLUDED

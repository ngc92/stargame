#ifndef CGAMEOBJECT_H_INCLUDED
#define CGAMEOBJECT_H_INCLUDED

#include "IGameObject.h"
#include "property/CPropertyObject.h"

namespace game
{
	/*! \class CGameObject
		\brief default implementation for IGameObject.
		\details ....
	*/
	class CGameObject : public IGameObject, public property::CPropertyObject,
					   ObjectCounter<CGameObject>
	{
		public:
			CGameObject(b2Body* body = nullptr, long ID = -1);
			virtual ~CGameObject();

			/// called just after the object is constructed and added to the world.
			void onInit() override;
			void onStep() override;
			void onImpact(IGameObject* other, const ImpactInfo& info) override;

			/// gets the current position of the game object
			b2Vec2 position() const final;
			/// gets the current rotation angle.
			float angle() const final;
			/// gets the current velocity.
			b2Vec2 velocity() const final;
			/// gets the current angular velocity.
			float angular_velocity() const final;
			/// gets an ID for object identification.
			long id() const final;

			/// adds a module to this game object.
			void addModule( std::shared_ptr<IGameObjectModule> ) final;

			/// adds a listener that is called every step for this game object.
			ListenerRef addStepListener( std::function<void()> lst ) final;
			/// adds a listener that is called when this object is hit by another game object.
			ListenerRef addImpactListener( std::function<void(IGameObjectView*, const ImpactInfo&)> lst ) final;

			/// get a pointer to the internal body, if any
			const b2Body* body() const final;

			/// get a pointer to the internal body, if any
			b2Body* getBody() final;

			/// marks this body for deletion.
			void remove() final;

			/// return whether the game object is considered to be alive, or marked for deletion.
			bool isAlive() const final;

		private:
			b2Body* mBody = nullptr;

			// status
			bool mIsAlive;

			// id
			long mID;

			ListenerList<> mStepListeners;
			ListenerList<IGameObject*, const ImpactInfo&> mImpactListeners;

			// modules
			module_vec& getModules() final { return mModules; };
			std::vector<std::shared_ptr<IGameObjectModule>> mModules;
	};
}

#endif // CGAMEOBJECT_H_INCLUDED

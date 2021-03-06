#ifndef CGAMEOBJECT_H_INCLUDED
#define CGAMEOBJECT_H_INCLUDED

#include "../IGameObject.h"
#include "property/CPropertyObject.h"
#include "../physics/body.h"
#include "property/TypedProperty.h"
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
			CGameObject(uint64_t ID, std::string type, ObjectCategory cateogry, b2Body* body = nullptr, std::string name = "object");
			virtual ~CGameObject();

			/// called just after the object is constructed and added to the world.
			void onInit(IGameWorld& world) override;
			void step(const IGameWorld& world, WorldActionQueue& push_action) override;
			void onStep(const IGameWorld& world) const override;
			void onImpact(IGameObject& other, const ImpactInfo& info) override;
			void dealDamage( const Damage& damage, const b2Vec2& pos, const b2Vec2& dir ) override;

			/// gets the current position of the game object
			b2Vec2 position() const final;
			/// gets the current rotation angle.
			float angle() const final;
			/// gets the current velocity.
			b2Vec2 velocity() const final;
			/// gets the current angular velocity.
			float angular_velocity() const final;
			/// gets an ID for object identification.
			uint64_t id() const final;
			/// gets the object type. This is the type that
			/// was used to get the spawn data for the object.
			const std::string& type() const final;
			/// the category of this object. 
			ObjectCategory category() const final;

			/// collision filter data. This is currently very specialised, so maybe a more general
			/// interface would be nice. However, we need to ensure that this does not cost performance for objects
			/// that do not require special collision handling.
			/// Right now, we can set one specific body with which this object shall not collide.
			const b2Body* ignoreCollisionTarget() const final;

			/// sets the body which shall be ignored upon collision checks
			void setIgnoreCollisionTarget( const b2Body* ignore ) final;



			/// adds a module to this game object.
			void addModule( std::shared_ptr<IGameObjectModule> ) final;

			/// adds a listener that is called every step for this game object.
			ListenerRef addStepListener( std::function<void(const IGameObjectView&)> lst ) final;
			/// adds a listener that is called when this object is hit by another game object.
			ListenerRef addImpactListener( std::function<void(IGameObjectView&, const ImpactInfo&)> lst ) final;
			/// adds a listener that is called when the object is removed
			ListenerRef addRemoveListener( std::function<void(const IGameObjectView&)> lst ) final;

			/// get a pointer to the internal body, if any
			const Body& body() const final;

			/// get a pointer to the internal body, if any
			Body& getBody() final;

			/// marks this body for deletion.
			void remove() final;

			/// return whether the game object is considered to be alive, or marked for deletion.
			bool isAlive() const final;

		private:
			Body mBody;

			const b2Body* mIgnoreBody = nullptr;

			// status
			bool mIsAlive;
			bool mInitialized = false;

			// id
			const uint64_t mID;
			property::TypedProperty<std::string> mType;
			property::TypedProperty<int> mCategory;

			ListenerList<const IGameObjectView&> mStepListeners;
			ListenerList<const IGameObjectView&> mRemoveListeners;
			ListenerList<IGameObject&, const ImpactInfo&> mImpactListeners;

			// modules
			module_vec& getModules() final { return mModules; };
			std::vector<std::shared_ptr<IGameObjectModule>> mModules;
	};
}

#endif // CGAMEOBJECT_H_INCLUDED

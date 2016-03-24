#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "util.h"
#include "util/ListenerList.h"

namespace game
{
	class IPropertyVisitor;

	struct ImpactInfo
	{
		b2Fixture* 	fixture;
		b2Vec2 		normal;
		b2Vec2		position;
		float		impulse;
	};

	class GameObject : ObjectCounter<GameObject>, noncopyable,
					   public std::enable_shared_from_this<GameObject>
	{
		public:
			GameObject(b2Body* body = nullptr, long ID = -1);
			virtual ~GameObject();

			void onStep();
			void onImpact(GameObject* other, const ImpactInfo& info);

			/// \note implementations in derived classes should manually call
			/// this base class method.
			virtual void visitProperties(IPropertyVisitor& visitor) const;

			void setPosition(const vector2d& pos);
			void setRotation(float rot);
			void setVelocity(const vector2d& vel);

			vector2d getPosition() const;
			float getRotation() const;
			vector2d getVelocity() const;
			float getAngularVelocity() const;

			const b2Body* getBody() const
			{
				return mBody;
			}

			b2Vec2 getVelocityInLocalPoint(const b2Vec2& p);
			float rayCast( b2Vec2 p1, b2Vec2 p2 ) const;
			bool testPoint( b2Vec2 point ) const;

			void remove();
			virtual void destroyObject();

			// coordinate conversion
			b2Vec2 getLocalPoint( b2Vec2 worldPoint ) const;
			b2Vec2 getWorldPoint( b2Vec2 localPoint ) const;

			b2Vec2 getLocalVector( b2Vec2 worldVector ) const;
			b2Vec2 getWorldVector( b2Vec2 localVector ) const;

			long getID() const { return mID; };

			bool isAlive() const { return mIsAlive; };

			void setYOffset( float o ) { mYOffset = o; };

			template<class T>
			ListenerRef addStepListener(T&& l)
			{
				return std::move(mStepListeners.addListener(std::forward<T>(l)));
			}

			template<class T>
			ListenerRef addImpactListener(T&& l)
			{
				return std::move(mImpactListeners.addListener(std::forward<T>(l)));
			}


		protected:

			b2Body* mBody = nullptr;
			// corrections
			float mYOffset = 0;

			// status
			bool mIsAlive;

			// id
			long mID;

			ListenerList<void> mStepListeners;
			ListenerList<GameObject*, const ImpactInfo&> mImpactListeners;
	};
}

#endif // GAMEOBJECT_H_INCLUDED

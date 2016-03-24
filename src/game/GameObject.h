#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "util.h"

namespace game
{
	class GameObject : ObjectCounter<GameObject>
	{
		public:
			GameObject(b2Body* body = nullptr, long ID = -1);
			virtual ~GameObject() = default;

			virtual void step() = 0;

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

		protected:

			b2Body* mBody = nullptr;
			// corrections
			float mYOffset = 0;

			// status
			bool mIsAlive;

			// id
			long mID;
	};
}

#endif // GAMEOBJECT_H_INCLUDED

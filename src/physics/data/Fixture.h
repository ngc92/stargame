#ifndef FIXTURE_H_INCLUDED
#define FIXTURE_H_INCLUDED

#include "Shape.h"
#include <boost/variant.hpp>

namespace physics
{
	namespace data
	{
		/// \todo transform this into a class that checks invariants
		class Fixture
		{
		public:
			using shape_t = boost::variant<PolygonShape, CircleShape>;
			
			Fixture( shape_t shape );
			
			// Setters
			Fixture& setFriction( float f );
			Fixture& setRestitution( float r );
			Fixture& setDensity( float d );
			Fixture& setSensor( bool s );
			Fixture& setShape( shape_t shape );
			
			// Getters
			float friction() const       { return mFriction; }
			float restitution() const    { return mRestitution; }
			float density() const        { return mDensity; }
			bool  is_sensor() const      { return mIsSensor; }
			const shape_t& shape() const { return mShape; }
		
		private:
			float mFriction    = 0.9;
			float mRestitution = 0.9;
			float mDensity     = 1;
			bool  mIsSensor    = false;
			shape_t mShape;
		};
	}
}

#endif // FIXTURE_H_INCLUDED

#ifndef SUNITCONVERTER_H_INCLUDED
#define SUNITCONVERTER_H_INCLUDED

class b2Vec2;

namespace physics
{
namespace data
{
    class CircleShape;
    class PolygonShape;
    class Fixture;
    class KinematicState;
    class BodyDef;
}

namespace simulation
{
	
	/*! \brief Class responsible for running the physics simulation
		\details This class runs the physics simulation itself.
				This means that it:
					* steps the Box2D world.
					* manages callbacks for physics events.
					* converts between game and Box2D units.
	*/
	class SUnitConverter
	{
	public:
		SUnitConverter(double metertoBox);
		
		// unit conversion interface
		/// Gets the conversion factor from game meters to Box2D meters.
		/// This should probably be set in the constructor of the implementation class, and remain unchanged.
		double getMeterToBox() const;
		
		/// converts game meters to Box2D meters.
		double metersToBox(double mks) const;
		/// converts Box2D meters to game meters.
		double boxToMeters(double box) const;
		
		/// converts game meters to Box2D meters (vector).
		/// \attention If your vector has not the dimension of length, this function is not applicable.
		b2Vec2 metersToBox(const b2Vec2& mks) const;
		/// converts Box2D meters to game meters (vector).
		/// \attention If your vector has not the dimension of length, this function is not applicable.
		b2Vec2 boxToMeters(const b2Vec2& box) const;
		
		// advanced conversion functions
		/// converts a circle shape from game to box units.
		data::CircleShape toBoxUnits( const data::CircleShape& original ) const;
		
		/// converts a circle shape from box to game units.
		data::CircleShape toGameUnits( const data::CircleShape& original ) const;
		
		/// converts a polygon shape from game to box units.
		data::PolygonShape toBoxUnits( const data::PolygonShape& original ) const;
		
		/// converts a polygon shape from box to game units.
		data::PolygonShape toGameUnits( const data::PolygonShape& original ) const;
		
		/// converts a polygon shape from game to box units.
		data::Fixture toBoxUnits( const data::Fixture& original ) const;
		
		/// converts a polygon shape from box to game units.
		data::Fixture toGameUnits( const data::Fixture& original ) const;
		
		/// converts a kinematic state from game to box units.
		data::KinematicState toBoxUnits( const data::KinematicState& original ) const;
		
		/// converts a kinematic state from box to game units.
		data::KinematicState toGameUnits( const data::KinematicState& original ) const;
		
		/// converts a BodyDef from game to box units.
		data::BodyDef toBoxUnits( const data::BodyDef& original ) const;
		
		/// converts a BodyDef from box to game units.
		data::BodyDef toGameUnits( const data::BodyDef& original ) const;
    private:
        double mMeterToBox;
	};
}
}

#endif // IUNITCONVERTER_H_INCLUDED

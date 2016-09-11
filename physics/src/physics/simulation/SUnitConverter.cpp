#include "SUnitConverter.h"
#include "physics/data/Shape.h"
#include "physics/data/Fixture.h"
#include "physics/data/Body.h"
#include <algorithm>

namespace physics
{
namespace simulation
{
    using data::CircleShape;
    using data::PolygonShape;
    using data::Fixture;

    SUnitConverter::SUnitConverter(double metertoBox) : mMeterToBox(metertoBox)
    {
    	if(mMeterToBox <= 0)
			BOOST_THROW_EXCEPTION( std::logic_error("trying to set up unit converter with negative coefficient.") );
    	
    }
    
    double SUnitConverter::getMeterToBox() const
    {
        return mMeterToBox;
    }
    
    double SUnitConverter::metersToBox(double mks) const
    {
        return mks * mMeterToBox;
    }
    
    double SUnitConverter::boxToMeters(double box) const
    {
        return box / mMeterToBox;
    }
    
    b2Vec2 SUnitConverter::metersToBox(const b2Vec2& mks) const
    {
        return b2Vec2( metersToBox(mks.x), metersToBox(mks.y) );
    }
    
    b2Vec2 SUnitConverter::boxToMeters(const b2Vec2& box) const
    {
        return b2Vec2( boxToMeters(box.x), boxToMeters(box.y) );
    }
    
    /// converts a circle shape from game to box units.
    CircleShape SUnitConverter::toBoxUnits( const CircleShape& original ) const
    {
        return CircleShape( metersToBox(original.radius()), metersToBox(original.center()) );
    }
    
    /// converts a circle shape from box to game units.
    CircleShape SUnitConverter::toGameUnits( const CircleShape& original ) const
    {
        return CircleShape( boxToMeters(original.radius()), boxToMeters(original.center()) );
    }
    
    /// converts a polygon shape from game to box units.
    PolygonShape SUnitConverter::toBoxUnits( const PolygonShape& original ) const
    {
        std::vector<b2Vec2> vertices = original.vertices();
        std::transform( begin(vertices), end(vertices), begin(vertices), [this](const b2Vec2& v) { return metersToBox(v); } );
        PolygonShape ret;
        ret.setVertices( std::move(vertices) );
        return ret;
    }
    
    /// converts a polygon shape from box to game units.
    PolygonShape SUnitConverter::toGameUnits( const PolygonShape& original ) const
    {
        std::vector<b2Vec2> vertices = original.vertices();
        std::transform( begin(vertices), end(vertices), begin(vertices), [this](const b2Vec2& v) { return boxToMeters(v); } );
        PolygonShape ret;
        ret.setVertices( std::move(vertices) );
        return ret;
    }
    
    struct ToBoxVisitor : public boost::static_visitor< Fixture::shape_t >
    {
        ToBoxVisitor(const SUnitConverter& c) : converter(c) { }
        const SUnitConverter& converter;
        template<class T>
        Fixture::shape_t operator()(const T& original) const
        {
            return converter.toBoxUnits( original );
        }
    };
    
    struct ToGameVisitor : public boost::static_visitor< Fixture::shape_t >
    {
        ToGameVisitor(const SUnitConverter& c) : converter(c) { }
        const SUnitConverter& converter;
        template<class T>
        Fixture::shape_t operator()(const T& original) const
        {
            return converter.toGameUnits( original );
        }
    };
    
    /// converts a polygon shape from game to box units.
    data::Fixture SUnitConverter::toBoxUnits( const data::Fixture& original ) const
    {
        /// \todo convert density
        Fixture copy = original;
        copy.setShape( boost::apply_visitor(ToBoxVisitor{*this}, original.shape()) );
        return copy;
    }
    
    /// converts a polygon shape from box to game units.
    data::Fixture SUnitConverter::toGameUnits( const data::Fixture& original ) const
    {
        /// \todo convert density
        Fixture copy = original;
        copy.setShape( boost::apply_visitor(ToGameVisitor{*this}, original.shape()) );
        return copy;
    }
    
    /// converts a kinematic state from game to box units.
	data::KinematicState SUnitConverter::toBoxUnits( const data::KinematicState& original ) const
	{
		data::KinematicState copy = original;
		copy.setPosition( metersToBox(original.position()) );
		copy.setVelocity( metersToBox(original.velocity()) );
		return copy;
	}
	
	/// converts a kinematic state shape from box to game units.
	data::KinematicState SUnitConverter::toGameUnits( const data::KinematicState& original ) const
	{
		data::KinematicState copy = original;
		copy.setPosition( boxToMeters(original.position()) );
		copy.setVelocity( boxToMeters(original.velocity()) );
		return copy;
	}
	
	/// converts a BodyDef from game to box units.
	data::BodyDef SUnitConverter::toBoxUnits( const data::BodyDef& original ) const
	{
		data::BodyDef copy = original;
		copy.setPosition( metersToBox(original.position()) );
		copy.setVelocity( metersToBox(original.velocity()) );
		return copy;
	}
	
	/// converts a BodyDef from box to game units.
	data::BodyDef SUnitConverter::toGameUnits( const data::BodyDef& original ) const
	{
		data::BodyDef copy = original;
		copy.setPosition( boxToMeters(original.position()) );
		copy.setVelocity( boxToMeters(original.velocity()) );
		return copy;
	}
}
}

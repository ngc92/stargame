#ifndef TACTICALMAPICON_H_INCLUDED
#define TACTICALMAPICON_H_INCLUDED

#include <string>
class b2Vec2;

namespace graphic
{
	/*! \class ITacticalMapIcon
		\brief Interface for an icon on the tactical map.
		\details This combines info about team, location, angle and
			objects type to be processed by the tactical map. Whenever 
			a new object is added to the map, an ITacticalMapIcon 
			pointer is returned, which can be used to update the 
			object infos.
	*/
	class ITacticalMapIcon
	{
	public:
		ITacticalMapIcon() = default;
		virtual ~ITacticalMapIcon() = default;
		
		virtual int team() const = 0;
		virtual const std::string& type() const = 0;
		 
		virtual const b2Vec2& position() const = 0;
		virtual void setPosition( const b2Vec2& pos ) = 0;
		 
		virtual float angle() const = 0;
		virtual void setAngle(float ang) = 0;
	};
}

#endif // TACTICALMAPICON_H_INCLUDED

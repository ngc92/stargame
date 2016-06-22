#ifndef CTACTICALMAPICON_H_INCLUDED
#define CTACTICALMAPICON_H_INCLUDED

#include "ITacticalMapIcon.h"
#include <Box2D/Common/b2Math.h>


namespace graphic
{
	namespace detail 
	{
		class CTacticalMapIcon : public ITacticalMapIcon
		{
		public:
			CTacticalMapIcon(int team, std::string type, b2Vec2 pos, float angle = 0);
			
			int team() const final;
			const std::string& type() const final;
			
			const b2Vec2& position() const final;
			void setPosition( const b2Vec2& pos ) final;
			
			float angle() const final;
			void setAngle(float ang) final;
			
		private:
			b2Vec2 mPosition;
			float mAngle = 0;
			int mTeam = 0;
			std::string mType = "";
		};
	}
}

#endif // CTACTICALMAPICON_H_INCLUDED

#ifndef RADAR_SCREEN_H_INCLUDED
#define RADAR_SCREEN_H_INCLUDED

#include <irrlicht/IGUIElement.h>
#include <vector>
#include <map>

namespace graphic
{
	using namespace irr;
	using gui::IGUIElement;
	using video::SColor;
	using video::ITexture;

	struct RadarReflex
	{
		enum Relation
		{
			FRIEND = 0,
			FOE,
			NEUTRAL
		};
		enum Kind
		{
			SHIP,
			MISSILE
		};
		core::vector2df position;
		Relation relation;
		Kind kind;
	};

	class RadarScreen : public IGUIElement
	{
		public:
			RadarScreen(gui::IGUIEnvironment* env, IGUIElement* parent, s32 id, core::recti rect);
			virtual ~RadarScreen();

			void draw() override;
			void OnPostRender(u32 time) override;

			// display configuration
			SColor getColorCode(RadarReflex::Relation rel) const;
			void setColorCode(RadarReflex::Relation rel, SColor color);
			void setShipTexture(ITexture* tex);

			// radar configuration
			void setRange( f32 range );
			f32 getRange() const;

			// current radar situation
			void setRadarReflexes(std::vector<RadarReflex> reflexes);
			std::vector<RadarReflex>& getRadarReflexes();

		private:
			// textures
			ITexture* mShipMarkerTexture;
			ITexture* mMissileMarkerTexture;
			ITexture* mWarningTexture;

			// colors
			std::map<RadarReflex::Relation, SColor> mColorCodes;
			SColor mBeamColor;

			// radar situation
			std::vector<RadarReflex> mReflexes;

			// state
			irr::u32 mOldTime;
			irr::f32 mCurrentAngle;
			bool mMissileWarning;

			// settings
			irr::f32 mRange;
			irr::f32 mRotationSpeed;
	};
}

#endif

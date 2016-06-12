#ifndef SPACESHIPSTATUSVIEW_H_INCLUDED
#define SPACESHIPSTATUSVIEW_H_INCLUDED

#include "IShipStatusView.h"
#include <vector>
#include <deque>

namespace Game
{
	class Spaceship;
	class GameObject;
}

class b2Vec2;

namespace graphic
{
	using namespace irr;

	using gui::IGUIElement;
	using video::SColor;
	using video::ITexture;

	class CShipStatusView final : public IShipStatusView
	{
		public:
			CShipStatusView(gui::IGUIEnvironment* env, IGUIElement* parent, s32 id, core::recti rect);
			virtual ~CShipStatusView();

			void draw() override;
			void OnPostRender(u32 time) override;

			// push spaceship information into this view.
			u32 addArmourSegment( core::vector2df p1, core::vector2df p2 ) override;
			void setSegmentStatus(u32 segment, f32 status) override;

			void setStructureStatus(f32 stat) override;

		private:

            int mDamageMarkerLifetime = 1500;
            float mDangerousDamageThreshold = 100;

            unsigned int mOldTime;

            struct DamageMarker
            {
                irr::core::vector2di gfx_pos;
				int deletion_timer;
				float damage_dealt;
				bool ricochet;
            };

            struct ArmourSegment
            {
            	core::vector2df p1;
            	core::vector2df p2;
            	f32 status;
            };

			std::deque<DamageMarker> mDamageMarkers;
			std::vector<ArmourSegment> mArmourSegments;

            // helper vars
            core::rectf mBoundingRect;
            // pre-calculated positional drawing offset
			core::position2di mPositionOffset;
			f32 mScaleFactor;

            // ship status
            f32 mTotalHealth = 1;
	};
}



#endif // SPACESHIPSTATUSVIEW_H_INCLUDED

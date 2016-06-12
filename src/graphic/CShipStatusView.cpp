#include "CShipStatusView.h"
#include <iostream>
#include <algorithm>
#include <irrlicht/IVideoDriver.h>
#include <irrlicht/IGUIEnvironment.h>


namespace graphic
{
	core::vector2di fti(const core::vector2df& v)
	{
		return core::vector2di(v.X, v.Y);
	}

	CShipStatusView::CShipStatusView( gui::IGUIEnvironment* guienv, IGUIElement* parent, s32 id, core::recti rect )
		: IShipStatusView(guienv, parent, id, std::move(rect))
	{
	}

	CShipStatusView::~CShipStatusView()
	{
	}

	u32 CShipStatusView::addArmourSegment( core::vector2df p1, core::vector2df p2 )
	{
		mBoundingRect.addInternalPoint(p1);
		mBoundingRect.addInternalPoint(p2);

		mScaleFactor = std::min( AbsoluteRect.getWidth() / mBoundingRect.getWidth(), AbsoluteRect.getHeight() / mBoundingRect.getHeight() );
		mPositionOffset = AbsoluteRect.getCenter() - fti(mScaleFactor * mBoundingRect.getCenter());

		mArmourSegments.push_back(ArmourSegment{p1, p2, 1.f});

		return mArmourSegments.size()-1;
	}

	void CShipStatusView::setSegmentStatus(u32 segment, f32 status)
	{
		mArmourSegments.at(segment).status = status;
	}

	void CShipStatusView::setStructureStatus(f32 stat)
	{
		mTotalHealth = stat;
	}

	void CShipStatusView::draw()
	{
		video::IVideoDriver* driver = Environment->getVideoDriver();
		driver->setTransform(video::ETS_WORLD, core::IdentityMatrix);
		// draw armour segment
		for( const auto& segment : mArmourSegments)
		{
			auto p1 = fti(mScaleFactor * segment.p1) + mPositionOffset;
			auto p2 = fti(mScaleFactor * segment.p2) + mPositionOffset;
			driver->draw2DLine( p1, p2, video::SColor(255, 255*(1-segment.status),255*segment.status, 0));
		}

		driver->draw2DPolygon( AbsoluteRect.getCenter(), 10, video::SColor(255, 255*(1 - mTotalHealth) ,255 * mTotalHealth, 0));

		for( auto dmg : mDamageMarkers)
		{
			auto color = video::SColor(255, 255, 0, 0);
			color.setAlpha( 255 * dmg.deletion_timer / mDamageMarkerLifetime );
			color.setGreen( 255 * std::max(0.0, 1.0 - dmg.damage_dealt / mDangerousDamageThreshold));
			driver->draw2DPolygon( dmg.gfx_pos, dmg.ricochet ? 3 : 4, color);
		}

	}

	void CShipStatusView::OnPostRender(irr::u32 time)
	{
		if(mOldTime == 0)
			mOldTime = time;

		// update deletion timers
		for(auto& marker : mDamageMarkers)
            marker.deletion_timer -= time - mOldTime;

		auto rem = std::remove_if(mDamageMarkers.begin(), mDamageMarkers.end(), [](const DamageMarker& m ) { return m.deletion_timer < 0;});
		mDamageMarkers.resize( std::distance(mDamageMarkers.begin(), rem) );

		mOldTime = time;
	}

/*	void SpaceshipStatusView::damageCallback( const Game::GameObject* source, b2Vec2 position, float damage, bool r )
	{
		position *= FACTOR / 2 * mScaleFactor;
		auto pos = core::vector2di(position.x, position.y) + mPositionOffset;
		mDamageMarkers.push_back(DamageMarker{pos, mDamageMarkerLifetime, damage, r});
	}
*/
}

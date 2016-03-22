#include "RadarScreen.h"

#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/IVideoDriver.h>
#include <cmath>
#include <iostream>

namespace graphic
{
	using namespace irr;
	RadarScreen::RadarScreen( gui::IGUIEnvironment* guienv, IGUIElement* parent, s32 id, core::recti rect )
		: IGUIElement(gui::EGUIET_ELEMENT, guienv, parent, id, rect),
			mRange(300), mOldTime(0), mCurrentAngle(0),
			mRotationSpeed(0.004)
	{
		mShipMarkerTexture = guienv->getVideoDriver()->getTexture("radar_ship_marker.png");
		mShipMarkerTexture->grab();
		guienv->getVideoDriver()->makeColorKeyTexture(mShipMarkerTexture, SColor(255,0,0,0));

		mMissileMarkerTexture = guienv->getVideoDriver()->getTexture("radar_missile_marker.png");
		mMissileMarkerTexture->grab();
		guienv->getVideoDriver()->makeColorKeyTexture(mMissileMarkerTexture, SColor(255,0,0,0));

		mWarningTexture = guienv->getVideoDriver()->getTexture("danger.png");
		mWarningTexture->grab();

		// default colors
		mColorCodes[RadarReflex::FRIEND] = SColor(255, 0, 255, 0);
		mColorCodes[RadarReflex::FOE] = SColor(255, 255, 0, 0);
		mColorCodes[RadarReflex::NEUTRAL] = SColor(255, 255, 255, 0);
		mBeamColor = SColor(255, 0, 128, 0);
	}

	RadarScreen::~RadarScreen()
	{
		mShipMarkerTexture->drop();
		mMissileMarkerTexture->drop();
		mWarningTexture->drop();
	}

	void RadarScreen::setRange( f32 sc )
	{
    	mRange = sc;
	}

	f32 RadarScreen::getRange() const
	{
		return mRange;
	}

	void RadarScreen::draw()
	{
		video::IVideoDriver* driver = Environment->getVideoDriver();
		core::recti source = core::recti( core::vector2di(0,0), mShipMarkerTexture->getSize() );

		for(auto& ref : mReflexes)
		{
			core::vector2df relc((ref.position.X / mRange), (ref.position.Y / mRange));
			if( relc.getLengthSQ() > 1.0)
				continue;

			core::vector2di sp = core::vector2di( 0.5 * relc.X * AbsoluteRect.getWidth(), 0.5 * relc.Y * AbsoluteRect.getHeight() );

			sp += AbsoluteRect.getCenter() - source.getSize()/2;

			SColor& color = mColorCodes[ref.relation];
			switch(ref.kind)
			{
			case RadarReflex::SHIP:
				driver->draw2DImage(mShipMarkerTexture, sp, source, &AbsoluteRect, color, true);
			break;
			case RadarReflex::MISSILE:
				driver->draw2DImage(mMissileMarkerTexture, sp, source, &AbsoluteRect, mColorCodes[RadarReflex::NEUTRAL], true);
			break;
			}
		}

		// draw current radar direction
		core::vector2di beam_end( 0.5 * std::cos(mCurrentAngle) * AbsoluteRect.getHeight(), 0.5 * std::sin(mCurrentAngle) * AbsoluteRect.getWidth());
		driver->draw2DLine( AbsoluteRect.getCenter(),  AbsoluteRect.getCenter() + beam_end, mBeamColor );

		// draw missile warning
		if( mMissileWarning )
		{
			irr::core::recti source( core::vector2di(0,0), mWarningTexture->getSize());
			driver->draw2DImage( mWarningTexture, AbsoluteRect.UpperLeftCorner, source, 0, SColor(255, 255, 255, 255), true );
		}
	}

	void RadarScreen::OnPostRender(u32 time )
	{
		if(mOldTime == 0)
			mOldTime = time;

		mCurrentAngle += (time - mOldTime) * mRotationSpeed;
		mOldTime = time;
	}

	void RadarScreen::setRadarReflexes(std::vector<RadarReflex> reflexes)
	{
		mReflexes = std::move(reflexes);
	}

	std::vector<RadarReflex>& RadarScreen::getRadarReflexes()
	{
		return mReflexes;
	}

	SColor RadarScreen::getColorCode(RadarReflex::Relation rel) const
	{
		return mColorCodes.at(rel);
	}

	void RadarScreen::setColorCode(RadarReflex::Relation rel, SColor color)
	{
		mColorCodes[rel] = color;
	}

	void RadarScreen::setShipTexture(ITexture* tex)
	{
		mShipMarkerTexture = tex;
	}
}

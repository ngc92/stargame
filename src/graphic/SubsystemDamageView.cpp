#include "SubsystemDamageView.h"
#include <irrlicht/IVideoDriver.h>
#include <irrlicht/IGUIEnvironment.h>
#include <irrlicht/IGUIStaticText.h>


namespace graphic
{
	using namespace irr;
	SubsystemDamageView::SubsystemDamageView( gui::IGUIEnvironment* guienv, IGUIElement* parent, s32 id, core::recti rect )
		: IGUIElement(gui::EGUIET_ELEMENT, guienv, parent, id, rect),
		mHealthyColor(255, 255, 128, 0),
		mDamageColor(255, 64, 32, 0),
		mTextColor(255, 255, 128, 0),
		mBarHeight(15)
	{
	}

	SubsystemDamageView::~SubsystemDamageView()
	{

	}

	std::shared_ptr<ISubSysStatus> SubsystemDamageView::addSubSystem(const std::string& name)
	{
		auto data = std::make_shared<SubSystemData>();

		core::recti rect(0, 0, 100, 20);
		data->textfield = Environment->addStaticText( L"", rect, false, false, this);

		data->name = name;
		mComponents.push_back( data );
		layout();

		return data;
	}

	void SubsystemDamageView::layout()
	{
		auto pos = core::position2di(0,0);
		int comp_count = mComponents.size();

		// fix absolute rect
		float row_height = AbsoluteRect.getHeight() / comp_count;
		float width = AbsoluteRect.getWidth();
		if( row_height < mBarHeight + 5)
			row_height = mBarHeight + 5;

		mMaxTextWidth = 0;

		for( auto& c : mComponents )
		{
			c->textfield->setRelativePosition(pos);
			c->textfield->setText( core::stringw(c->name.c_str()).c_str() );
			c->textfield->setOverrideColor( mTextColor );
			c->base_rect = core::recti(pos.X, pos.Y, pos.X + width, pos.Y + mBarHeight);
			pos.Y += row_height;
			mMaxTextWidth = std::max(mMaxTextWidth, c->textfield->getTextWidth() + 5);
		}
	}

	void SubsystemDamageView::draw()
	{
		video::IVideoDriver* driver = Environment->getVideoDriver();
		auto pos = RelativeRect.UpperLeftCorner;

		for(const auto& c : mComponents )
		{
			core::recti rect = c->base_rect + pos;
			rect.UpperLeftCorner.X += mMaxTextWidth;

			driver->draw2DRectangle( mDamageColor, rect );
			float status = 1.0 - c->status;
			rect.LowerRightCorner.X -= rect.getWidth() * status;
			driver->draw2DRectangle( mHealthyColor, rect );
		}

		IGUIElement::draw();
	}

	void SubsystemDamageView::OnPostRender(irr::u32 time)
	{
	}

	void SubsystemDamageView::setTextColor(const SColor& c)
	{
		mTextColor = c;
		layout();
	}

	//! Writes attributes of the element.
	//! Implement this to expose the attributes of your element for
	//! scripting languages, editors, debuggers or xml serialization purposes.
	void SubsystemDamageView::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const
	{
		IGUIElement::serializeAttributes(out, options);

		out->addColor ("HealthColor", mHealthyColor);
		out->addColor ("DamageColor", mDamageColor);
		out->addColor ("TextColor",   mTextColor);
		out->addInt   ("BarHeight",   mBarHeight);
	}


	//! Reads attributes of the element
	void SubsystemDamageView::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0)
	{
		IGUIElement::deserializeAttributes(in, options);

		mHealthyColor = in->getAttributeAsColor("HealthColor");
		mDamageColor  = in->getAttributeAsColor("DamageColor");
		mTextColor    = in->getAttributeAsColor("TextColor");
		mBarHeight    = in->getAttributeAsInt("BarHeight");
	}

}

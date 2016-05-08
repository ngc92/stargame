#include "CTacticalMapView.h"
#include "CTacticalMapIcon.h"
#include <irrlicht/IVideoDriver.h>
#include <irrlicht/IGUIEnvironment.h>
#include <iostream>
#include "util/io.h"


namespace graphic
{
namespace detail
{
	CTacticalMapView::CTacticalMapView(gui::IGUIEnvironment* env, IGUIElement* parent, s32 id, core::recti rect):
		ITacticalMapView(env, parent, id, rect), mScroll(0, 0)
	{

	}

	CTacticalMapView::~CTacticalMapView()
	{

	}

	void CTacticalMapView::draw()
	{
		video::IVideoDriver* driver = Environment->getVideoDriver();

		// draw all registered objects
		for(auto& w_obj : mObjects)
		{
			auto obj = w_obj.lock();
			if(!obj)
				continue;

			// convert position to irrlicht
			auto box_pos = mZoom * (obj->position() + mScroll);
			core::vector2di pos(box_pos.x, box_pos.y);

			core::recti rect(pos, core::dimension2di(10, 10));
			rect += getAbsolutePosition().UpperLeftCorner;
			driver->draw2DRectangle( SColor(255, 255, 255, 255), rect );
		}
		IGUIElement::draw();
	}

	std::shared_ptr<ITacticalMapIcon> CTacticalMapView::addObject( b2Vec2 pos, float angle, int team, std::string type )
	{
		auto icon =  std::make_shared<detail::CTacticalMapIcon>(team, std::move(type), std::move(pos), angle);
		mObjects.push_back(icon);
		return icon;
	}

	void CTacticalMapView::OnPostRender(u32 time)
	{
		IGUIElement::OnPostRender(time);
	}

	//! Writes attributes of the element.
	void CTacticalMapView::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
	{

	}

	//! Reads attributes of the element
	void CTacticalMapView::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
	{

	}
}
}

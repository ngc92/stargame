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
		#ifndef NDEBUG
		setDebugName( "CTacticalMapView" );
		#endif
		
		// load textures!
		/// \todo not here
		mIconSymbols["ship"] = env->getVideoDriver()->getTexture("gfx/ship.png");
		
		mTeamColors[0] = SColor(255, 0, 200, 0);
		mTeamColors[1] = SColor(255, 200, 0, 0);
	}

	CTacticalMapView::~CTacticalMapView()
	{

	}

	void CTacticalMapView::draw()
	{
		video::IVideoDriver* driver = Environment->getVideoDriver();
		auto boundary = getAbsolutePosition();
		driver->draw2DRectangleOutline( boundary, SColor(255, 255, 255, 255) );

		// draw all registered objects
		for(auto& w_obj : mObjects)
		{
			auto obj = w_obj.lock();
			if(!obj)
				continue;

			// convert position to irrlicht
			auto box_pos = mZoom * (obj->position() + mScroll);
			core::vector2di pos(box_pos.x, box_pos.y);

			auto ico = mIconSymbols.find(obj->type());
			if(ico != mIconSymbols.end())
			{
				SColor colors[4];
				colors[0] =  mTeamColors[obj->team()];
				colors[1] =  mTeamColors[obj->team()];
				colors[2] =  mTeamColors[obj->team()];
				colors[3] =  mTeamColors[obj->team()];
				
				core::recti rect(pos, core::dimension2di(10, 10));
				rect += boundary.UpperLeftCorner;
				driver->draw2DImage( ico->second, rect, core::recti(ico->second->getSize()), &boundary, colors );
			} 
			 else 
			{
				core::recti rect(pos, core::dimension2di(5, 5));
				rect += getAbsolutePosition().UpperLeftCorner;
				driver->draw2DRectangle( SColor(255, 255, 255, 255), rect );
			}
			
		}
		
		/// \todo remove old objects
		
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
	
	bool CTacticalMapView::OnEvent( const SEvent &event ) 
	{
		if ( isEnabled() )
		{
			switch( event.EventType )
			{
			case EET_MOUSE_INPUT_EVENT:
			{
				if(event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN)
				{
					auto selection = pickElement( event.MouseInput.X, event.MouseInput.Y );
				}
			}
			break;
			default:
			break;
			}
		}

		return Parent ? Parent->OnEvent( event ) : false;
	}
	
	std::shared_ptr<ITacticalMapIcon> CTacticalMapView::pickElement( s32 x, s32 y )
	{
		for(auto& w_obj : mObjects)
		{
			auto obj = w_obj.lock();
			if(!obj)
				continue;
				
			auto box_pos = mZoom * (obj->position() + mScroll);
			core::recti rect(box_pos.x, box_pos.y, 10, 10);
			rect += getAbsolutePosition().UpperLeftCorner;
			if( rect.isPointInside( core::vector2di(x, y)) )
			{
				return obj;
			}
		}
		
		return nullptr;
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

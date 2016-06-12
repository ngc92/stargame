#ifndef TACTICALMAPVIEW_H_INCLUDED
#define TACTICALMAPVIEW_H_INCLUDED

#include "util.h"

#include <irrlicht/IGUIElement.h>

namespace graphic
{
	class ITacticalMapIcon;

	using namespace irr;
	using irr::gui::IGUIElement;

	class ITacticalMapView : public IGUIElement
	{
	public:
		ITacticalMapView(gui::IGUIEnvironment* env, IGUIElement* parent, s32 id, core::recti rect) :
			IGUIElement(gui::EGUIET_ELEMENT, env, parent, id, rect)
		{
		}

		virtual ~ITacticalMapView() = default;

		/// objects are internally saved as weak_ptr, so to remove the object from the map just
		/// delete the shared_ptr
		virtual std::shared_ptr<ITacticalMapIcon> addObject( b2Vec2 pos, float angle, int team, std::string type ) = 0;
	};
}

#endif // TACTICALMAPVIEW_H_INCLUDED

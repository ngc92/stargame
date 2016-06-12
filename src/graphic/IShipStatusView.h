#ifndef ISHIPSTATUSVIEW_H_INCLUDED
#define ISHIPSTATUSVIEW_H_INCLUDED

#include <utility>
#include <irrlicht/IGUIElement.h>

class b2Vec2;

namespace graphic
{
	using namespace irr;

	using gui::IGUIElement;

	class IShipStatusView : public IGUIElement
	{
		public:
			IShipStatusView(gui::IGUIEnvironment* env, IGUIElement* parent, s32 id, core::recti rect)  :
				IGUIElement(gui::EGUIET_ELEMENT, env, parent, id, std::move(rect)) {}
			virtual ~IShipStatusView() = default;

			// push spaceship information into this view.
			virtual u32 addArmourSegment( core::vector2df p1, core::vector2df p2 ) = 0;
			virtual void setSegmentStatus(u32 segment, f32 status) = 0;

			virtual void setStructureStatus(f32 stat) = 0;
	};
}


#endif // ISHIPSTATUSVIEW_H_INCLUDED

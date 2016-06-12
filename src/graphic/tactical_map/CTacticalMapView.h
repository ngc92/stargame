#ifndef CTACTICALMAPVIEW_H_INCLUDED
#define CTACTICALMAPVIEW_H_INCLUDED

#include "ITacticalMapView.h"

#include <vector>
#include <memory>
#include <unordered_map>

namespace graphic
{
namespace detail
{
	using namespace irr;
	using video::SColor;

	class CTacticalMapView : public ITacticalMapView
	{
	public:
		CTacticalMapView(gui::IGUIEnvironment* env, IGUIElement* parent, s32 id, core::recti rect);
		virtual ~CTacticalMapView();

		void draw() override;
		void OnPostRender(u32 time) override;

		/// objects are internally saved as weak_ptr, so to remove the object from the map just
		/// delete the shared_ptr
		std::shared_ptr<ITacticalMapIcon> addObject( b2Vec2 pos, float angle, int team, std::string type ) override;


		//! called if an event happened.
		bool OnEvent( const SEvent &event ) override;

		//! Writes attributes of the element.
		void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const override;

		//! Reads attributes of the element
		void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options) override;
	private:
		std::shared_ptr<ITacticalMapIcon> pickElement( s32 x, s32 y );

		// view position on the tactical map
		b2Vec2 mScroll;
		float mZoom = 0.1;

		// gfx config
		std::unordered_map<std::string, video::ITexture*> mIconSymbols;
		std::unordered_map<int, SColor> mTeamColors;

		// object list
		std::vector<std::weak_ptr<ITacticalMapIcon>> mObjects;

	};
}
}

#endif // CTACTICALMAPVIEW_H_INCLUDED

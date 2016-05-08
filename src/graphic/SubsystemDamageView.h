#ifndef SUBSYSTEMDAMAGEVIEW_H_INCLUDED
#define SUBSYSTEMDAMAGEVIEW_H_INCLUDED

#include <irrlicht/IGUIElement.h>
#include <memory>
#include <vector>

namespace irr
{
	namespace gui
	{
		class IGUIStaticText;
	}
}

namespace graphic
{
	using namespace irr;
	using irr::gui::IGUIElement;
	using irr::video::SColor;
	using irr::video::ITexture;

	struct ISubSysStatus
	{
		f32 status;
	};

	struct SubSystemData : public ISubSysStatus
	{
		std::string name;
		gui::IGUIStaticText* textfield;
		core::recti base_rect;
	};

	class SubsystemDamageView : public IGUIElement
	{
		public:
			SubsystemDamageView(gui::IGUIEnvironment* env, IGUIElement* parent, s32 id, core::recti rect);
			virtual ~SubsystemDamageView();

			virtual void draw();
			virtual void OnPostRender(u32 time);

			std::shared_ptr<ISubSysStatus> addSubSystem(const std::string& name);

			// config functions
			u32 getBarHeight() const { return mBarHeight; };
			void setBarHeight(u32 h) { mBarHeight = h; };

			const SColor& getHealthColor() const { return mHealthyColor; };
			const SColor& getDamageColor() const { return mDamageColor; };
			const SColor& getTextColor()   const { return mTextColor; };
			void setHealthColor(const SColor& c) { mHealthyColor = c; };
			void setDamageColor(const SColor& c) { mDamageColor = c; };
			void setTextColor(const SColor& c);

			//! Writes attributes of the element.
			void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const override;

			//! Reads attributes of the element
			void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options) override;


		private:
			// this function rearranges the layout.
			void layout();

			std::vector<std::shared_ptr<SubSystemData>> mComponents;

			// dynamic layout vars
			s32 mMaxTextWidth;

			// configuration
			SColor mHealthyColor;
			SColor mDamageColor;
			SColor mTextColor;
			u32 mBarHeight;
	};
}


#endif // SUBSYSTEMDAMAGEVIEW_H_INCLUDED

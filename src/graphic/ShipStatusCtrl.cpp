#include "ShipStatusCtrl.h"
#include "IShipStatusView.h"

#include "property/property.h"
#include "game/IGameObjectView.h"

namespace graphic
{
	// local namespace so we do not accidentially clash ODR's
	namespace
	{
		float getHP(const property::IPropertyObjectView& p)
		{
			using boost::get;
			return get<float>(p.getProperty("HP").value()) / get<float>(p.getProperty("maxHP").value());
		};

		void process_subobject(IShipStatusView* view, const property::IPropertyObjectView& subobj)
		{
			using boost::get;

			if(subobj.name().substr(0, 6) == "armour")
			{
				auto p1 = get<b2Vec2>( subobj.getProperty("p1").value() );
				auto p2 = get<b2Vec2>( subobj.getProperty("p2").value() );

				view->addArmourSegment( irr::core::vector2df(p1.x, p1.y), irr::core::vector2df(p2.x, p2.y) );
			}
		}
	}

	ShipStatusControl::ShipStatusControl(IShipStatusView* view, const game::IGameObjectView& ship)
	{
		auto& structure = ship.getChild("structure");
		structure.forallChildren([view](const property::IPropertyObjectView& subobj){ process_subobject(view, subobj); });

		auto updateHP = [view](property::IPropertyView& p)
		{
			view->setStructureStatus( getHP(*p.owner()) );
		};

		structure.getProperty("HP").addListener(updateHP);
		structure.getProperty("maxHP").addListener(updateHP);
	}
}

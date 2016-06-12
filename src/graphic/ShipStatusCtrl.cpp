#include "ShipStatusCtrl.h"
#include "IShipStatusView.h"

#include "property/property.h"
#include "game/IGameObjectView.h"

#include <iostream>

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

		void process_subobject(std::vector<ListenerRef>& listeners, IShipStatusView* view, const property::IPropertyObjectView& subobj)
		{
			using boost::get;
			using std::placeholders::_1;

			if(subobj.name().substr(0, 6) == "armour")
			{
				auto p1 = get<b2Vec2>( subobj.getProperty("p1").value() );
				auto p2 = get<b2Vec2>( subobj.getProperty("p2").value() );

				int seg_id = view->addArmourSegment( irr::core::vector2df(p1.x, p1.y), irr::core::vector2df(p2.x, p2.y) );
				auto updateHP = [view](int id, property::IPropertyView& p)
				{
					view->setSegmentStatus( id, getHP(*p.owner()) );
				};

				listeners.push_back(subobj.getProperty("armour.HP").addListener(std::bind(updateHP, seg_id, _1)));
				listeners.push_back(subobj.getProperty("armour.maxHP").addListener(std::bind(updateHP, seg_id, _1)));
			}
		}
	}

	ShipStatusControl::ShipStatusControl(IShipStatusView* view, const game::IGameObjectView& ship)
	{
		auto& structure = ship.getChild("structure");
		structure.forallChildren([view, this](const property::IPropertyObjectView& subobj){ process_subobject(mListeners, view, subobj); });

		auto updateHP = [view](property::IPropertyView& p)
		{
			view->setStructureStatus( getHP(*p.owner()) );
		};

		mListeners.push_back(structure.getProperty("HP").addListener(updateHP));
		mListeners.push_back(structure.getProperty("maxHP").addListener(updateHP));
	}
}

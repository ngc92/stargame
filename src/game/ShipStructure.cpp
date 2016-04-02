#include "ShipStructure.h"
#include "Components/IComponent.h"
#include <Box2D/Collision/b2Collision.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>

#include "Components/FuelTank.h"
#include "Components/Engine.h"

namespace game
{
	ShipStructure::ShipStructure()
	{
		addStructureCell(StructureCell(0,1000,nullptr));
	}

	void ShipStructure::addStructureCell(StructureCell cell)
	{
		mCells.push_back( std::move(cell) );
	}

	void ShipStructure::addComponent(std::size_t cellid, std::shared_ptr<IComponent> cmp)
	{
		getCell(cellid).addComponent( std::move(cmp) );
	}

	void ShipStructure::init(property::IPropertyObject& parent, IActionListInterface& actions, input::IInputCollection& inputs)
	{
		foreachComponent([](IComponent& c,
							property::IPropertyObject& p,
							IActionListInterface& l,
							input::IInputCollection& i)
							{
											c.init(l, i);
											p.addChild(&c);
							},
							std::ref(parent), std::ref(actions), std::ref(inputs)
						);
	}

	void ShipStructure::update(IActionListInterface& actions)
	{
		foreachComponent([](IComponent& c, IActionListInterface& l){ c.step(l); }, std::ref(actions));
	}

	void ShipStructure::hit(Damage damage, vector2d position, vector2d direction)
	{
		// check that position is not inside the ship, otherwise move!


		// first, raytrace against armour to find hit segment
		b2RayCastInput rcin{position, position + direction, 1000};
		b2RayCastOutput rcout;
		b2Transform trafo;
		trafo.SetIdentity();
		ArmourSegment* armour_hit = nullptr;
		for(auto& seg : mArmour)
		{
			b2EdgeShape temp;
			temp.Set(seg.p1, seg.p2);
			if(temp.RayCast(&rcout, rcin, trafo, 0))
			{
				rcin.maxFraction = rcout.fraction;
				armour_hit = &seg.armour;
			}
		}

		// if there was an armour segment that was hit.
		if(armour_hit)
		{
			damage = armour_hit->hit(damage);
		}

		// now, for the internal segments
		struct HitCell
		{
			float frac;
			StructureCell* cell;
		};
		rcin.maxFraction = 10000;
		std::vector<HitCell> hit_cells;
		for(auto& cell : mCells)
		{
			if(cell.shape().RayCast(&rcout, rcin, trafo, 0))
			{
				rcin.maxFraction = rcout.fraction;
				hit_cells.push_back(HitCell{rcout.fraction, &cell});
			}
		}

		// sort hits
		std::sort( hit_cells.begin(), hit_cells.end(), [](HitCell a, HitCell b) { return a.frac < b.frac; } );

		// now go through all cells and hit the components
		/// \todo make damage processing more interesting here!
		float internal_damage = 0.5 * damage.getTotalDamage();
		mStructurePoints -= internal_damage;
		for(auto& hc : hit_cells)
		{
			StructureCell* cell = hc.cell;
			std::size_t comp_count = cell->components().size();
			float cmp_dmg = internal_damage / comp_count;
			for(auto& c : cell->components())
				internal_damage -= c->damage(cmp_dmg);
		}

		/// \todo hit event listener, including ship destruction
	}

	float ShipStructure::getMaxHP() const
	{
		return mMaxStructurePoints;
	}

	float ShipStructure::getCurrHP() const
	{
		return mStructurePoints;
	}

	float ShipStructure::getWeight() const
	{
		return mTotalWeight;
	}

	float ShipStructure::getBaseWeight() const
	{
		return mBaseWeight;
	}

	StructureCell& ShipStructure::getCell(std::size_t id)
	{
		using namespace std;
		auto it = find_if(begin(mCells), end(mCells), [id](const StructureCell& c){ return c.id() == id;});
		assert(it != mCells.end());
		return *it;
	}
}

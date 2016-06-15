#include "CSubStructure.h"
#include "game/physics/body.h"
#include "game/physics/fixture.h"
#include "util/io.h"
#include "components/IComponent.h"
#include "IDamageSource.h"
#include <Box2D/Collision/b2Collision.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Dynamics/b2Body.h>
#include <boost/iterator/indirect_iterator.hpp>

#include "property/CProperty.h"
#include <iostream>

namespace game
{
	CSubStructure::CSubStructure() :
		CPropertyObject("structure"),
		mStructurePoints("HP", this, 100),
		mMaxStructurePoints("maxHP", this, 100),
		mBaseWeight("baseweight", this, 100)
	{
	}

	CSubStructure::~CSubStructure()
	{

	}

	IStructureCell* CSubStructure::addStructureCell( std::unique_ptr<IStructureCell> cell)
	{
		/// \todo check uniqueness of ID!
		mCells.push_back( std::move(cell) );
		return mCells.back().get();
	}

	ArmourSegment* CSubStructure::addArmourSegment(vector2d p1, vector2d p2, ArmourSegment seg)
	{
		mArmour.push_back( PosArmourSegment{p1, p2, std::make_unique<ArmourSegment>( std::move(seg) )} );
		return mArmour.back().armour.get();
	}

	IStructureCell* CSubStructure::getCellByID( long id )
	{
		for(auto& cell : mCells )
			if(cell->id() == id)
			return cell.get();
		return nullptr;
	}

	void CSubStructure::onInit(IGameObject& object, IGameWorld& world)
	{
		// init all components
		foreachComponent([](IComponent& component, IGameObject& object){component.init(object);}, std::ref(object));

		// need to write the component subobject loop ourselves here, because we need the shared_ptr
		// build the physic body
		for(auto& cell : mCells)
		{
			auto fixture = physics::Fixture::create(object.getBody(), cell->shape(), 10.f);
			fixture.setRestitution(0.1);
			fixture.setFriction(0.5);
			for(std::size_t i = 0; i < cell->component_count(); ++i)
			{
				addChild(cell->getComponent(i));
				fixture.addMass(cell->getComponent(i)->weight());
			}
		}

		// add the armour segments to the object definition
		for(unsigned i = 0; i < mArmour.size(); ++i)
		{
			auto pob = std::make_shared<property::CPropertyObject>("armour" + to_string(i));
			addChild(pob);
			pob->addChild(mArmour[i].armour->getSharedPropertyObject());
			pob->addProperty( property::CProperty::create("p1", pob.get(), mArmour[i].p1) );
			pob->addProperty( property::CProperty::create("p2", pob.get(), mArmour[i].p2) );
		}
	}

	void CSubStructure::onStep(IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action)
	{
		foreachComponent([](IComponent& c, IGameObject& o, const IGameWorld& w, WorldActionQueue& p){ c.step(o, w, p);},
		std::ref(object), std::ref(world), std::ref(push_action));
		if(mStructurePoints <= 0)
		{
			object.remove();
		}
	}

	/// this function is called whenever another game object hits the current one.
	void CSubStructure::onImpact( IGameObject& object, IGameObject& other, const ImpactInfo& info)
	{
	}

	void CSubStructure::onDamage( IGameObject& object, const Damage& damage, const b2Vec2& pos, const b2Vec2& dir )
	{
		hit(object.body().body()->GetTransform(), damage, pos, dir);
	}

	void CSubStructure::hit(const b2Transform& trafo, Damage damage, vector2d position, vector2d direction)
	{
		// check that position is not inside the ship, otherwise move!


		// first, raytrace against armour to find hit segment
		b2RayCastInput rcin{position, position + direction, 1000};
		b2RayCastOutput rcout;
		ArmourSegment* armour_hit{};
		for(auto& seg : mArmour)
		{
			b2EdgeShape temp;
			temp.Set(seg.p1, seg.p2);
			if(temp.RayCast(&rcout, rcin, trafo, 0))
			{
				rcin.maxFraction = rcout.fraction;
				armour_hit = seg.armour.get();
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
			IStructureCell* cell;
		};
		rcin.maxFraction = 10000;
		std::vector<HitCell> hit_cells;
		for(auto& cell : mCells)
		{
			if(cell->shape().RayCast(&rcout, rcin, trafo, 0))
			{
				rcin.maxFraction = rcout.fraction;
				hit_cells.push_back(HitCell{rcout.fraction, cell.get()});
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
			IStructureCell* cell = hc.cell;
			std::size_t comp_count = cell->component_count();
			float cmp_dmg = internal_damage / comp_count;
			for(auto& c : cell->components())
			{
				internal_damage -= c.damage(cmp_dmg);
			}
		}

		/// \todo hit event listener, including ship destruction
	}

	void CSubStructure::registerAtAI( ai::IAIRegistrator& reg )
	{
		foreachComponent([](auto& component, auto reg){component.registerAtAI(reg);}, std::ref(reg));
	}

	float CSubStructure::maxHP() const
	{
		return mMaxStructurePoints;
	}

	float CSubStructure::HP() const
	{
		return mStructurePoints;
	}

	float CSubStructure::weight() const
	{
		return mTotalWeight;
	}

	float CSubStructure::baseWeight() const
	{
		return mBaseWeight;
	}

	auto CSubStructure::getCells() -> cell_range_t
	{
		using idt = boost::indirect_iterator<decltype(mCells.begin())>;
		return cell_range_t( idt(begin(mCells)), idt(end(mCells)) );
	}
}

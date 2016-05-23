#include "Definitions.h"
#include "property/CPropertyObject.h"
#include "property/CProperty.h"
#include <boost/property_tree/ptree.hpp>
#include <regex>
#include <iostream>

#include "consts.h"
#include "factory.h"
#include "game/object_module/IStructureCell.h"
#include "game/object_module/ISubStructure.h"
#include "game/object_module/ArmourSegment.h"
#include "game/object_module/components/IComponent.h"

namespace game
{
namespace spawn
{
	// helpers

	b2Vec2 read_position( const boost::property_tree::ptree& tree )
	{
		return b2Vec2{tree.get<float>("x") * METERS_TO_BOX, tree.get<float>("y") * METERS_TO_BOX };
	}

	b2Vec2 read_position( const boost::property_tree::ptree& tree, const vertex_cache_t& vcache  )
	{
		auto vname = tree.get_value<std::string>();
		if( vname != "" )
		{
			return vcache.at(vname);
		}
		else
		{
			return read_position(tree);
		}
	}

	// ------------------------------------------------------------

	Component::Component(const boost::property_tree::ptree& props) :
		mType( props.get<std::string>("type") ),
		mHitPoints( props.get<float>("HP") ),
		mWeight( props.get<float>("weight")),
		mProperties( std::make_shared<property::CPropertyObject>( "data" ) )
	{
		auto subs = props.get_child("properties");
		for(auto& data : subs )
		{
			const std::string& s = data.second.get_value<std::string>();
			property::data_t value = s;
			// check if number
			if(std::regex_match(s, std::regex("-?[0-9]+([.][0-9]+)?")))
			{
				value = data.second.get_value<float>();
			}

			mProperties->addProperty( property::CProperty::create(data.first, mProperties.get(), value ) );
		}
	}

	const std::string& Component::type() const
	{
		return mType;
	}

	float Component::HP() const
	{
		return mHitPoints;
	}

	float Component::weight() const
	{
		return mWeight;
	}

	const property::IPropertyObject& Component::getProperties() const
	{
		return *mProperties;
	}

	std::shared_ptr<IComponent> Component::create() const
	{
		std::shared_ptr<components::IComponent> component = constructComponent(type());

		// set hitpoints, maxHP and weight
		component->setHitPoints( HP(), HP() );
		component->setWeight( weight() );

		// set other attributes
		mProperties->forallProperties(
			[&component](property::IPropertyView& prop)
			{
				*component->getPropertyPtr(prop.name()) = prop.value();
			}
		);

		return component;
	}

	// ------------------------------------------------------------------------------------------------

	StructureCell::StructureCell(const boost::property_tree::ptree& props,
					  const vertex_cache_t& vertex_cache):
		mID( props.get<int>("ID") ),
		mMaxLoad( props.get<float>("max_load") )
	{
		auto shape = props.get_child("shape");
		std::vector<b2Vec2> vertices;
		for(auto& prop : shape)
		{
			assert(prop.first == "vertex");
			vertices.push_back( read_position(prop.second, vertex_cache) );
		}

        mShape.Set(vertices.data(), vertices.size());
	}

	long StructureCell::id() const
	{
		return mID;
	}

	float StructureCell::maxLoad() const
	{
		return mMaxLoad;
	}

	const b2PolygonShape& StructureCell::shape() const
	{
		return mShape;
	}

	std::unique_ptr<IStructureCell> StructureCell::create() const
	{
		return createStructureCell(mID, mMaxLoad, make_unique<b2PolygonShape>(mShape));
	}


	// ----------------------------------------------------------------
	Hull::Hull(const boost::property_tree::ptree& props)
	{
		std::unordered_map<std::string, b2Vec2> vertex_cache;
		// get vertex cache, if any
		auto vcache_o = props.get_child_optional("vertices");
		if( vcache_o )
		{
			auto vcache = vcache_o.get();

			for(auto& prop : vcache)
			{
				assert(prop.first == "vertex");
				auto name = prop.second.get<std::string>("name");
				std::cout << "add vertex " << name << "\n";
				vertex_cache[name] = read_position(prop.second);
			}
		}
		auto cells = props.get_child("cells");
		for(auto& prop : cells)
		{
			assert(prop.first == "cell");
			mCells.push_back( StructureCell(prop.second, vertex_cache) );
		}

		auto armour = props.get_child("armour");
		for(auto& segment : armour)
		{
			assert(segment.first == "segment");
			auto start = read_position(segment.second.get_child("start"), vertex_cache);
			auto end = read_position(segment.second.get_child("end"), vertex_cache);
			float hp = segment.second.get<float>("hitpoints");
			mArmour.push_back( {start, end, hp} );
		}
	}

	auto Hull::cells() const -> const cell_vec_t&
	{
		return mCells;
	}

	auto Hull::armour() const -> const armour_vec_t&
	{
		return mArmour;
	}

	std::shared_ptr<ISubStructure> Hull::create() const
	{
		std::shared_ptr<ISubStructure> ss = createSubStructure();
		for(const auto& c : mCells)
		{
			ss->addStructureCell( c.create() );
		}

		for(const auto& c : mArmour)
		{
			ss->addArmourSegment(c.p1, c.p2, ArmourSegment(c.hp));
		}

		return ss;
	}

	// ------------------------------------------------------------

	Ship::Ship(const boost::property_tree::ptree& props):
		mHull( props.get<std::string>("hull") ),
		mName( props.get<std::string>("name") )
	{
		auto comps = props.get_child("components");
		for(auto& comp : comps )
		{
			assert(comp.first == "component");
			std::string type = comp.second.get<std::string>("type");
			int cell = comp.second.get<int>("cell");
			mComponents.push_back( {std::move(type), cell} );
		}

		auto attribs = props.get_child("attributes");
		for(auto& attr : attribs)
		{
			mAttributes.insert( {attr.first, attr.second.get_value<std::string>()} );
		}
	}

	const std::string& Ship::hull() const
	{
		return mHull;
	}

	const std::string& Ship::name() const
	{
		return mName;
	}

	auto Ship::components() const -> const cmp_vec_t&
	{
		return mComponents;
	}

	void Ship::addAttributes( property::IPropertyObject& obj ) const
	{
		for(auto& attrib : mAttributes)
		{
			obj.addProperty( property::CProperty::create(attrib.first, &obj, attrib.second) );
		}
	}


	// --------------------------------------------------------------
	Projectile::Projectile(const boost::property_tree::ptree& props):
		mName( props.get<std::string>("name") ),
		mPropellantVelocity( props.get<float>("velocity") ),
		mRadius( props.get<float>("radius") / 1000.f ),
		mMass( props.get<float>("mass") ),
		mLifetime( int(props.get<float>("lifetime") * STEPS_PER_SECOND) )
	{

	}

	const std::string& Projectile::name() const
	{
		return mName;
	}

	float Projectile::propellVelocity() const
	{
		return mPropellantVelocity;
	}

	float Projectile::radius() const
	{
		return mRadius;
	}

	float Projectile::mass() const
	{
		return mMass;
	}

	int Projectile::lifetime() const
	{
		return mLifetime;
	}

}
}

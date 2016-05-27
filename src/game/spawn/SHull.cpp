#include "SHull.h"
#include "spawn_util.h"
#include "factory.h"

#include "game/object_module/ISubStructure.h"
#include "game/object_module/ArmourSegment.h"


namespace game
{
namespace spawn
{
	// --------------------------------------------------------------------
	//		implementation of hull class
	// --------------------------------------------------------------------
	SHull::SHull(const boost::property_tree::ptree& props)
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
				vertex_cache[name] = read_position(prop.second);
			}
		}
		auto cells = props.get_child("cells");
		for(auto& prop : cells)
		{
			assert(prop.first == "cell");
			mCells.push_back( SStructureCell(prop.second, vertex_cache) );
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

	auto SHull::cells() const -> const cell_vec_t&
	{
		return mCells;
	}

	auto SHull::armour() const -> const armour_vec_t&
	{
		return mArmour;
	}

	std::shared_ptr<ISubStructure> SHull::create() const
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


	// --------------------------------------------------------------------
	// 		helper class for single cell of the hull - implementation
	// --------------------------------------------------------------------

	SStructureCell::SStructureCell(const boost::property_tree::ptree& props,
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

	long SStructureCell::id() const
	{
		return mID;
	}

	float SStructureCell::maxLoad() const
	{
		return mMaxLoad;
	}

	const b2PolygonShape& SStructureCell::shape() const
	{
		return mShape;
	}

	std::unique_ptr<IStructureCell> SStructureCell::create() const
	{
		return createStructureCell(mID, mMaxLoad, make_unique<b2PolygonShape>(mShape));
	}
}
}

#ifndef SHULL_H_INCLUDED
#define SHULL_H_INCLUDED

#include "Definitions.h"
#include "physics/data/Shape.h"

namespace game
{
namespace spawn
{
	// --------------------------------------------------------------------
	// 		helper class for single cell of the hull - definition
	// --------------------------------------------------------------------

	/// structure cell definition.
	class SStructureCell
	{
	public:
		SStructureCell(const boost::property_tree::ptree& props,
					  const vertex_cache_t& vertex_cache);

		long id() const;
		float maxLoad() const;
		const ::physics::data::PolygonShape& shape() const;

		std::unique_ptr<IStructureCell> create() const;
	private:
		long mID;
		float mMaxLoad;
		::physics::data::PolygonShape mShape;
	};

	// ---------------------------------------------------------------------
	/// basic ship structure without function
	class SHull
	{
		typedef std::vector<SStructureCell> cell_vec_t;
		struct Armour{ b2Vec2 p1; b2Vec2 p2; float hp; };
		typedef std::vector<Armour> armour_vec_t;
	public:
		SHull(const boost::property_tree::ptree& props);
		const cell_vec_t& cells() const;
		const armour_vec_t& armour() const;

		/// creates the (structural) part of the sub-structure of a ship.
		std::shared_ptr<ISubStructure> create() const;
	private:
		std::vector<SStructureCell> mCells;
		std::vector<Armour> mArmour;
	};
}
}

#endif // SHULL_H_INCLUDED

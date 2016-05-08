#ifndef COMPONENTDEFINITION_H_INCLUDED
#define COMPONENTDEFINITION_H_INCLUDED

#include <vector>
#include <boost/property_tree/ptree_fwd.hpp>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>
#include "game/fwd.h"

namespace property
{
	class IPropertyObject;
}

namespace game
{
namespace spawn
{
	/// component definition.
	class Component
	{
	public:
		Component( const boost::property_tree::ptree& props );

		// data getters
		const std::string& type() const;
		float HP() const;
		float weight() const;

		const property::IPropertyObject& getProperties() const;

		std::shared_ptr<IComponent> create() const;
	private:
		std::string mType;
		float mHitPoints;
		float mWeight;
		std::shared_ptr<property::IPropertyObject> mProperties;
	};

	/// structure cell definition.
	class StructureCell
	{
	public:
		StructureCell(const boost::property_tree::ptree& props);

		long id() const;
		float maxLoad() const;
		const b2PolygonShape& shape() const;

		std::unique_ptr<IStructureCell> create() const;
	private:
		long mID;
		float mMaxLoad;
		b2PolygonShape mShape;
	};


	/// basic ship structure without function
	class Hull
	{
		typedef std::vector<StructureCell> cell_vec_t;
		struct Armour{ b2Vec2 p1; b2Vec2 p2; float hp; };
		typedef std::vector<Armour> armour_vec_t;
	public:
		Hull(const boost::property_tree::ptree& props);
		const cell_vec_t& cells() const;
		const armour_vec_t& armour() const;

		/// creates the (structural) part of the sub-structure of a ship.
		std::shared_ptr<ISubStructure> create() const;
	private:
		std::vector<StructureCell> mCells;
		std::vector<Armour> mArmour;
	};

	// ------------------------------------------------
	class Ship
	{
		struct cmpdef
        {
        	std::string type;
        	int cell;
        };
        typedef std::vector<cmpdef> cmp_vec_t;
	public:
		Ship(const boost::property_tree::ptree& props);

		const std::string& hull() const;
		const std::string& name() const;
		const cmp_vec_t& components() const;
	private:
        std::string mHull;
        std::string mName;

        std::vector<cmpdef> mComponents;
	};
}
}

#endif // COMPONENTDEFINITION_H_INCLUDED

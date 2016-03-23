#include "StructureCell.h"
#include "Components/IComponent.h"
#include <Box2D/Collision/Shapes/b2Shape.h>

namespace game
{
	StructureCell::StructureCell(  std::size_t id, float maxload, std::unique_ptr<b2Shape> shape ) :
		mID(id),
		mMaxLoad(maxload),
		mShape(std::move(shape))
	{
	}

	StructureCell::~StructureCell()
	{
	}

	void StructureCell::addComponent(std::shared_ptr<IComponent> cmp)
	{
		// check weight
		float w = weight() + cmp->getWeight();
		assert( w < mMaxLoad );

		mComponents.push_back( std::move(cmp) );
	}

	float StructureCell::weight() const
	{
		float w = 0;
		for(auto& c : components())
			w += c->getWeight();
		return w;
	}

	float StructureCell::max_weight() const
	{
		return mMaxLoad;
	}

	const comp_vec_t& StructureCell::components() const
	{
		return mComponents;
	}

	const b2Shape& StructureCell::shape() const
	{
		return *mShape;
	}

	std::size_t StructureCell::id() const
	{
		return mID;
	}
}

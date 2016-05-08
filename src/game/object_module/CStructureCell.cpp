#include "CStructureCell.h"
#include "components/IComponent.h"
#include <Box2D/Collision/Shapes/b2Shape.h>
#include <boost/iterator/indirect_iterator.hpp>

namespace game
{
	CStructureCell::CStructureCell( long id, float maxload, std::unique_ptr<b2Shape> shape ) :
		mID(id),
		mMaxLoad(maxload),
		mShape(std::move(shape))
	{
	}

	CStructureCell::~CStructureCell()
	{
	}

	void CStructureCell::addComponent(std::shared_ptr<IComponent> cmp)
	{
		// check weight
		float w = weight();
		w += cmp->weight();
		assert( w < mMaxLoad );

		mComponents.push_back( std::move(cmp) );
	}

	long CStructureCell::id() const
	{
		return mID;
	}

	float CStructureCell::weight() const
	{
		float w = 0;
		for(auto& c : mComponents)
			w += c->weight();
		return w;
	}

	float CStructureCell::max_weight() const
	{
		return mMaxLoad;
	}

	auto CStructureCell::components() -> comp_range_t
	{
		using idt = boost::indirect_iterator<decltype(mComponents.begin())>;
		return comp_range_t( idt(begin(mComponents)), idt(end(mComponents)) );
	}

	const b2Shape& CStructureCell::shape() const
	{
		return *mShape;
	}

	std::size_t CStructureCell::component_count() const
	{
		return mComponents.size();
	}

	const std::shared_ptr<IComponent>& CStructureCell::getComponent(std::size_t index)
	{
		return mComponents.at(index);
	}
}

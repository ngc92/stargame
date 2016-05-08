#ifndef ISUBSTRUCTURE_H_INCLUDED
#define ISUBSTRUCTURE_H_INCLUDED

#include "common_includes.h"
#include "IStructureCell.h"
#include <boost/range/any_range.hpp>

namespace game
{
	class ArmourSegment;

    class ISubStructure : public IGameObjectModule
	{
	protected:
		typedef boost::any_range<IStructureCell, boost::forward_traversal_tag, IStructureCell&, std::ptrdiff_t> cell_range_t;

	public:
		/// adds the cell to the structure object, and returns a pointer to the new cell.
		virtual IStructureCell* addStructureCell(std::unique_ptr<IStructureCell> cell) = 0;

		/// adds a segment of armour and returns a pointer to it.
		virtual ArmourSegment* addArmourSegment(vector2d p1, vector2d p2, ArmourSegment seg) = 0;

		/// gets a sub-cell by id
		virtual IStructureCell* getCellByID( long id ) = 0;

		/// iterate over all subcells
		virtual cell_range_t getCells() = 0;

		/// structure info
		virtual float HP() const = 0;
		virtual float maxHP() const = 0;

		virtual float weight() const = 0;
		virtual float baseWeight() const = 0;

		/// \todo add convenience functions!

		// non-virtual convenience functions
		/*! \brief Calls function F for each component.
			\details Allows arbitrary constant arguments to be passed to the function.
			\param func Function to be called for each component. Has to take IComponent and Args as parameters
			\param args optional additional arguments to be passed to func.
		*/
		template<class F, class... Args>
		void foreachComponent(const F& func, Args&&... args);
	};


	// implementation of templates
	template<class F, class... Args>
	void ISubStructure::foreachComponent(const F& func, Args&&... args)
	{
		for(auto& cell : getCells())
		{
			for(auto& comp : cell.components())
			{
                func(comp, std::forward<Args>(args)...);
			}
		}
	}

}

#endif // ISUBSTRUCTURE_H_INCLUDED

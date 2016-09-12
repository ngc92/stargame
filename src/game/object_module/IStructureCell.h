#ifndef ISHIPSTRUCTURECELL_H_INCLUDED
#define ISHIPSTRUCTURECELL_H_INCLUDED

#include <memory>
#include <boost/range/any_range.hpp>
#include "game/fwd.h"
#include "physics/data/Shape.h"

namespace game
{
	
	/*! \class StructureCell
		\brief A single cell within the space ships structural built.
		\details A cell is a part of the space ship, which is localized and
				can hold one or more ship components.
	*/
	class IStructureCell
	{
		protected:
			typedef boost::any_range<IComponent, boost::forward_traversal_tag, IComponent&, std::ptrdiff_t> comp_range_t;
		public:
			IStructureCell( ) = default;
			virtual ~IStructureCell() = default;

			//! add a new component.
			virtual void addComponent(std::shared_ptr<IComponent> cmp) = 0;

			//! gets the id of the cell.
			virtual long id() const = 0;
			//! gets the current total weight
			virtual float weight() const = 0;
			//! gets the maximum total weight
			virtual float max_weight() const = 0;
			//! access to the cell's shape
			virtual const ::physics::data::Shape& shape() const = 0;
			//! access the components
			virtual comp_range_t components() = 0;
			//! get the number of components in the cell
			virtual std::size_t component_count() const = 0;
			//! get a component pointer
			virtual const std::shared_ptr<IComponent>& getComponent(std::size_t index) = 0;

			// listeners
			/// \todo weight change, damage
	};

}
#endif // SHIPSTRUCTURECELL_H_INCLUDED

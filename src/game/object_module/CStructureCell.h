#ifndef CSHIPSTRUCTURECELL_H_INCLUDED
#define CSHIPSTRUCTURECELL_H_INCLUDED

#include <vector>
#include "IStructureCell.h"

class b2Shape;

namespace game
{
	typedef std::vector<std::shared_ptr<IComponent>> comp_vec_t;
	/*! \class StructureCell
		\brief A single cell within the space ships structural built.
		\details A cell is a part of the space ship, which is localized and
				can hold one or more ship components.
	*/
	class CStructureCell: public IStructureCell
	{
		public:
			CStructureCell( long id, float maxload, std::unique_ptr<b2Shape> shape );
			~CStructureCell();
			CStructureCell(CStructureCell&&) = default;

			void addComponent(std::shared_ptr<IComponent> cmp) override;

			//! gets the id of the cell. Used by data specs to refer to cells.
			long id() const final;
			//! gets the current total weight
			float weight() const override;
			//! gets the maximum total weight
			float max_weight() const final;
			//! access to the cell's shape
			const b2Shape& shape() const final;
			//! access the components
			comp_range_t components() final;
			//! get the number of components in the cell
			std::size_t component_count() const final;
			//! get a component pointer
			const std::shared_ptr<IComponent>& getComponent(std::size_t index) final;
			// listeners
			/// \todo weight change, damage

		private:
			const long mID;						//! ID of the cell, cannot be changed after creation.
			float mMaxLoad; 					//!< maximum total weight all installed components here can have.
			comp_vec_t mComponents;				//!< components inside this cell.
			std::unique_ptr<b2Shape> mShape;	//!< the shape of this cell
	};

}
#endif // SHIPSTRUCTURECELL_H_INCLUDED

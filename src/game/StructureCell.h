#ifndef SHIPSTRUCTURECELL_H_INCLUDED
#define SHIPSTRUCTURECELL_H_INCLUDED

#include <vector>
#include <memory>

class IComponent;
class b2Shape;

namespace game
{
	typedef std::vector<std::shared_ptr<IComponent>> comp_vec_t;
	/*! \class StructureCell
		\brief A single cell within the space ships structural built.
		\details A cell is a part of the space ship, which is localized and
				can hold one or more ship components.
	*/
	class StructureCell
	{
		public:
			StructureCell( std::size_t id, float maxload, std::unique_ptr<b2Shape> shape );
			~StructureCell();
			StructureCell(StructureCell&&) = default;

			//! add a new component.
			void addComponent(std::shared_ptr<IComponent> cmp);

			//! gets the current total weight
			float weight() const;
			//! gets the maximum total weight
			float max_weight() const;
			//! access the component list.
			const comp_vec_t& components() const;
			//! access to the cell's shape
			const b2Shape& shape() const;
			//! get the id of the cell
			std::size_t id() const;

			// listeners
			/// \todo weight change, damage

		private:
			// identification
			const std::size_t mID;				//!< ID of the cell. Has to be unique and cannot be changed after creation.

			float mMaxLoad; 					//!< maximum total weight all installed components here can have.
			comp_vec_t mComponents;				//!< components inside this cell.
			std::unique_ptr<b2Shape> mShape;	//!< the shape of this cell
	};

}
#endif // SHIPSTRUCTURECELL_H_INCLUDED

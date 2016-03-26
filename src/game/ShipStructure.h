#ifndef SHIPSTRUCTURE_H_INCLUDED
#define SHIPSTRUCTURE_H_INCLUDED

#include "util.h"
#include <vector>

#include "StructureCell.h"
#include "ArmourSegment.h"

class IPropertyObject;

namespace input
{
	class IInputCollection;
}

namespace game
{
	class IActionListInterface;

	/*! \class ShipStructure
		\brief ShipStructure defines the global structure of the ship, i.e.
				its separation into cells.
		\details
	*/
	class ShipStructure : public ObjectCounter<ShipStructure>
	{
	public:

		ShipStructure();

		// build up the structure
		void addStructureCell(StructureCell cell);
		void addComponent(std::size_t cellid, std::shared_ptr<IComponent> cmp);

		/*! \brief Called when the spaceship is hit
			\param damage Damage of hit.
			\param position Position of hit in local coordinate system.
			\param direction Direction of hit in local coordinate system.
		*/
		void hit(Damage damage, vector2d position, vector2d direction);

		/// called on initialization
		void init(IActionListInterface& actions, input::IInputCollection& inputs);

		/// called every step
		void update(IActionListInterface& actions);

		// hitpoints, weight, etc
		float getMaxHP() const;
		float getCurrHP() const;

		float getWeight() const;
		float getBaseWeight() const;

		/// get cell based on ID
		StructureCell& getCell(std::size_t id);

		/*! \brief Calls function F for each component.
			\details Allows arbitrary constant arguments to be passed to the function.
			\param func Function to be called for each component. Has to take IComponent and Args as parameters
			\param args optional additional arguments to be passed to func.
		*/
		template<class F, class... Args>
		void foreachComponent(const F& func, Args&&... args);

		/*! \brief Calls function F for each cell shape.
			\details Allows arbitrary constant arguments to be passed to the function.
			\param func Function to be called for each component. Has to take b2Shape and Args as parameters
			\param args optional additional arguments to be passed to func.
		*/
		template<class F, class... Args>
		void foreachShape(const F& func, Args&&... args);

	private:
		// structure data
		float mStructurePoints;
		float mMaxStructurePoints;

		float mBaseWeight;
		float mTotalWeight;

		// internal cells
		std::vector<StructureCell> mCells;

		// armour
		struct PosArmourSegment
		{
			vector2d p1;
			vector2d p2;
			ArmourSegment armour;
		};

		std::vector<PosArmourSegment> mArmour;
	};

	// implementation of template method
	template<class F, class... Args>
	void ShipStructure::foreachComponent(const F& func, Args&&... args)
	{
		for(auto& cell : mCells)
		{
			for(auto& comp : cell.components())
			{
				func(*comp, std::forward<Args>(args)...);
			}
		}
	}

	template<class F, class... Args>
	void ShipStructure::foreachShape(const F& func, Args&&... args)
	{
		for(auto& cell : mCells)
		{
			func(cell.shape(), std::forward<Args>(args)...);
		}
	}
}

#endif // SHIPSTRUCTURE_H_INCLUDED

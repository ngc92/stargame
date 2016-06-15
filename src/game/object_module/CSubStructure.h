#ifndef SHIPSTRUCTURE_H_INCLUDED
#define SHIPSTRUCTURE_H_INCLUDED

#include "util.h"
#include "common_includes.h"
#include "ISubStructure.h"
#include <vector>

#include "IStructureCell.h"
#include "ArmourSegment.h"
#include "property/TypedProperty.h"

namespace game
{
	template<class T>
	using Property = property::TypedProperty<T>;

	/*! \class CSubStructure
		\brief CSubStructure defines the global structure of an object, e.g. a spaceship.
		\details
	*/
	class CSubStructure : public ObjectCounter<CSubStructure>, public ISubStructure, public property::CPropertyObject
	{
	public:

		CSubStructure();
		virtual ~CSubStructure();

		// build up the structure
		IStructureCell* addStructureCell(std::unique_ptr<IStructureCell> cell) final;
		ArmourSegment* addArmourSegment(vector2d p1, vector2d p2, ArmourSegment seg) final;

		IStructureCell* getCellByID( long id ) final;

		/// iterate over all subcells
		cell_range_t getCells() final;

		/*! \brief Called when the spaceship is hit
			\param damage Damage of hit.
			\param position Position of hit in local coordinate system.
			\param direction Direction of hit in local coordinate system.
		*/
		void hit(const b2Transform& trafo, Damage damage, vector2d position, vector2d direction);

		/// called on initialization
		void onInit( IGameObject& object, IGameWorld& world ) override;

		/// called every step
		void onStep( IGameObject& object, const IGameWorld& world, WorldActionQueue& push_action) override;

		/// this function is called whenever another game object hits the current one.
		void onImpact( IGameObject& object, IGameObject& other, const ImpactInfo& info) override;

		void onDamage( IGameObject& object, const Damage& damage, const b2Vec2& pos, const b2Vec2& dir ) override;

		void registerAtAI( ai::IAIRegistrator& reg ) override;

		// hitpoints, weight, etc
		float HP() const final;
		float maxHP() const final;

		float weight() const final;
		float baseWeight() const final;

		/*! \brief Calls function F for each cell shape.
			\details Allows arbitrary constant arguments to be passed to the function.
			\param func Function to be called for each component. Has to take b2Shape and Args as parameters
			\param args optional additional arguments to be passed to func.
		*/
		template<class F, class... Args>
		void foreachShape(const F& func, Args&&... args);
	private:
		// structure data
		Property<float> mStructurePoints;
		Property<float> mMaxStructurePoints;

		Property<float> mBaseWeight;
		float mTotalWeight;

		// internal cells
		std::vector<std::unique_ptr<IStructureCell>> mCells;

		// armour
		struct PosArmourSegment
		{
			vector2d p1;
			vector2d p2;
			std::unique_ptr<ArmourSegment> armour;
		};

		std::vector<PosArmourSegment> mArmour;
	};

	// --------------------------------------------------
	// 		template implementations
	// --------------------------------------------------

	template<class F, class... Args>
	void CSubStructure::foreachShape(const F& func, Args&&... args)
	{
		for(auto& cell : mCells)
		{
			func(cell->shape(), std::forward<Args>(args)...);
		}
	}
}

#endif // SHIPSTRUCTURE_H_INCLUDED

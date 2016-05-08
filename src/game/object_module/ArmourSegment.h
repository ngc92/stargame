#ifndef ARMOURSEGMENT_H_INCLUDED
#define ARMOURSEGMENT_H_INCLUDED

#include "game/Damage.h"
#include "property/TypedProperty.h"

namespace game
{
	template<class T>
	using Property = property::TypedProperty<T>;

	/*! \class ArmourSegment
		\brief A single segment of armour.
		\details This class models a single piece of outer space ship hull.
				It protects the ship, by the following damage model:

				Each ArmourSegment has an absorption value A. Incoming damage D is reduced
				by A, which is scaled by the armour status. D = D - A * HP/maxHP.

				The remaining damage is split into a transmitted part and a part that damages
				the armour itself.

	*/
	class ArmourSegment
	{
	public:
		ArmourSegment(float hp);
		ArmourSegment(float hp, Damage absorb, Damage transmit, Damage destruct);
		ArmourSegment(ArmourSegment&&) = default;
		~ArmourSegment();

		// info functions
		float hp() const;
		float max_hp() const;
		float hp_status() const;

		// armour functions
		Damage hit( Damage damage );

		const std::shared_ptr<property::IPropertyObject>& getSharedPropertyObject();
	private:
		// property object. needs to be initialised first
		std::shared_ptr<property::IPropertyObject> mProperties;
		
		// hitpoints of armour
		Property<float> mHP;
		Property<float> mMaxHP;

		// damage absorption
		Damage mAbsorbtion;
		Damage mTransmission;
		Damage mDestruction;
	};
}

#endif // ARMOURSEGMENT_H_INCLUDED

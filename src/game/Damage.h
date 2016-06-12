#ifndef DAMAGE_H_INCLUDED
#define DAMAGE_H_INCLUDED

#include <array>
#include <iosfwd>

namespace game
{
	enum class DamageType
	{
		PIERCE,
		BLUNT,
		THERMAL,
		COUNT
	};

	class Damage
	{
	public:
		/// default constructor (and const c'tor), initializes all damages to \p f ( = 0)
		Damage( float f = 0 );

		Damage(DamageType type, float value);
		/// convenience constructor for single damage type

		// get/set damage
		/// get type specific damage
		float getDamage( DamageType t ) const;
		/// set type specific damage
		void setDamage( DamageType t, float value);
		/// get total damage
		float getTotalDamage() const;

		// damage modifications
		/*! \brief absorbs \p absorbtion damage.
			\details substructs absorbtion from current damage values, but makes
					sure no damage value is decreased below zero.
		*/
		void absorb( const Damage& absorbtion );
	private:
		std::array<float, (unsigned int)DamageType::COUNT> mDamages;

		friend Damage& operator*=(Damage& d, const Damage& o);
		friend Damage& operator+=(Damage& d, const Damage& o);
		friend Damage& operator*=(Damage& d, float f);
	};

	// a few utility operators
	// scale damage by float
	Damage& operator*=(Damage& d, const Damage& o);
	Damage& operator+=(Damage& d, const Damage& o);
	Damage& operator*=(Damage& d, float f);
	Damage operator*(const Damage& d, const Damage& o);
	Damage operator+(const Damage& d, const Damage& o);
	Damage operator*(const Damage& d, float f);
}

std::ostream& operator<<(std::ostream& out, const game::Damage& damage);


#endif // DAMAGE_H_INCLUDED

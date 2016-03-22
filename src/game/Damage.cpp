#include "Damage.h"
#include <numeric>

namespace game
{
	Damage::Damage()
	{
		mDamages.fill(0);
	}

	Damage::Damage(DamageType type, float value)
	{
		mDamages.fill(0);
		setDamage(type, value);
	}

	float Damage::getDamage( DamageType t ) const
	{
        return mDamages.at((unsigned)t);
	}

	void Damage::setDamage( DamageType t, float value)
	{
		mDamages.at((unsigned)t) = value;
	}

	float Damage::getTotalDamage() const
	{
		using namespace std;
		return accumulate(begin(mDamages), end(mDamages), 0.0);
	}

	void Damage::absorb( const Damage& absorbtion )
	{
		for(unsigned i = 0; i < mDamages.size() ; ++i)
			mDamages[i] = std::max(0.f, mDamages[i] - absorbtion.mDamages[i]);
	}

	Damage& operator*=(Damage& d, const Damage& o)
	{
		for(unsigned i = 0; i < d.mDamages.size() ; ++i)
			d.mDamages[i] *= o.mDamages[i];
		return d;
	}

	Damage& operator+=(Damage& d, const Damage& o)
	{
		for(unsigned i = 0; i < d.mDamages.size() ; ++i)
			d.mDamages[i] += o.mDamages[i];
		return d;
	}

	Damage& operator*=(Damage& d, float f)
	{
		for(auto& v : d.mDamages)
			v *= f;
		return d;
	}

	Damage operator*(const Damage& d, const Damage& o)
	{
		Damage copy(d);
		copy *= o;
		return copy;
	}

	Damage operator+(const Damage& d, const Damage& o)
	{
		Damage copy(d);
		copy += o;
		return copy;
	}

	Damage operator*(const Damage& d, float f)
	{
		Damage copy(d);
		copy *= f;
		return copy;
	}
}

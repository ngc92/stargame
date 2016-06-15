#ifndef IWEAPONSYSTEM_H_INCLUDED
#define IWEAPONSYSTEM_H_INCLUDED


class b2Vec2;

namespace game
{
namespace ai
{
	/*! \class IWeaponSystem
		\brief Base class for anything that can shoot things.
		\details This interface defines the communication protocol between the
				AI and anything that can be used to accelerate/rotate the object.

				For that, it provides a set of info functions describing its capabilities,
				and action functions which try to implement the control commands as
				faithfully as possible (note that this might not always be the case, e.g.
				a fixed engine can only accelerate in one direction.)

		\todo	Add interface for booster-like objects.
		\todo 	Get direction dependent thrust.
	*/
	class IWeaponSystem
	{
	public:
		~IWeaponSystem() = default;

		// info functions


		// action functions
		virtual void fire() = 0;
	};
}
}

#endif // IWEAPONSYSTEM_H_INCLUDED

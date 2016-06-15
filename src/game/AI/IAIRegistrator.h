#ifndef IAIREGISTRATOR_H_INCLUDED
#define IAIREGISTRATOR_H_INCLUDED

namespace game
{
namespace ai
{
	class IPropulsionSystem;
	class IWeaponSystem;

	/** \brief class interface that allows registration of AI interfaces with the main AI.
	*/
	class IAIRegistrator
	{
	public:
		virtual ~IAIRegistrator() = default;

		virtual std::shared_ptr<void> registerPropulsionSystem( IPropulsionSystem& propsys ) = 0;
		virtual std::shared_ptr<void> registerWeaponSystem( IWeaponSystem& propsys ) = 0;
	};
}
}

#endif // IAIREGISTRATOR_H_INCLUDED

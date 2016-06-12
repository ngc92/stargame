#ifndef FWD_H_INCLUDED
#define FWD_H_INCLUDED

namespace listener
{

}

// forward declarations for game stuff
/*! \namespace game
	\brief Namespace for core game mechanics
	\details TODO
*/
namespace game
{
	// views
	class IGameObjectView;
	class IGameWorldView;

	class IGameWorld;
	class IGameObject;

	class IStructureCell;
	class ISubStructure;

	class SpaceShip;
	class FlightModel;

	namespace components
	{
		class IComponent;
	}

	using components::IComponent;
}


#endif // FWD_H_INCLUDED

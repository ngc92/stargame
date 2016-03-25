#ifndef FWD_H_INCLUDED
#define FWD_H_INCLUDED

// forward declarations for game stuff
namespace game
{
	class GameWorld;
	class SpaceShip;
	class FlightModel;
	class GameObject;
	namespace components
	{
		class IComponent;
	}

	using components::IComponent;
}


#endif // FWD_H_INCLUDED

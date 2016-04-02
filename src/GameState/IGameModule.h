#ifndef IGAMEMODULE_H_INCLUDED
#define IGAMEMODULE_H_INCLUDED

class ListenerRef;

namespace game
{
	class GameWorld;
	class GameObject;
}

class IGameModule
{
public:
	virtual ~IGameModule() = default;
	virtual void onSpawn(const game::GameObject& spawned) {};
	virtual void onStep(const game::GameWorld& view) {};
};

#endif // IGAMEMODULE_H_INCLUDED

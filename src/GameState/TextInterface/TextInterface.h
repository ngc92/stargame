#ifndef TEXTINTERFACE_H_INCLUDED
#define TEXTINTERFACE_H_INCLUDED

namespace game
{
	class GameWorld;
	class GameObject;
}

class TextInterface
{
public:
	void update(const game::GameWorld& view);
private:
	void handleObject( const game::GameObject& view );

};

#endif // TEXTINTERFACE_H_INCLUDED

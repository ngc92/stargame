#ifndef GAMEEDITORSTATE_H_INCLUDED
#define GAMEEDITORSTATE_H_INCLUDED

#include "IState.h"

class IEngine;

namespace game
{
	class Game;
}

class TextInterface;

class GameState: public IState
{
public:
	GameState(IEngine* engine);
	~GameState();

	// callbacks
	/// if this state is active, update is called every frame.
	void update() override;

	/// this is called after every drawing call has been made
	void onDraw() override;

	/// called when the state becomes active
	void onActivate() override;

	/// called when the state becomes inactive
	/// this function is not allowed to throw. If any problem occures while
	/// deactivating a state, logging an error is the preferred course of action.
	void onDeactivate() noexcept override;

	/// gets the states name
	const char* getName() const noexcept override;

	/// gets the GUI manager
	IGUIEnvironment* getGUIEnvironment() noexcept override;

	bool onEvent(const irr::SEvent::SGUIEvent& event) override;
private:
	IGUIEnvironment* mGUIEnv;
	std::unique_ptr<game::Game> mGame;
	std::unique_ptr<TextInterface> mInterface;
};

#endif // GAMEEDITORSTATE_H_INCLUDED

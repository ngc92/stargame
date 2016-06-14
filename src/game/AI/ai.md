## Micro AI {#micro_ai}
The lowest level of AI is implemented as a set of free functions in namespace game::ai. 
These functions return game::ai::Control objects, which specify (optionally) a steering vector 
and a desired angular acceleration to achieve their respective objective optimally.
Since the spaceship usually does not allow for acceleration according to the steering vector
(e.g. because of the alignment of the engines, or insufficient engine power etc), the function
game::ai::steer solves for a way to get as close to the desired steering as possible, and calculates
separate controls for each engine.

To facilitate the communication between the AI and the game object, the IPropulsionSystem is used. For
ships, any engine-like component implements this interface and registers itself with the AI in the 
init function.

## TODO
* move communication interface to ai namespace
* improve comm registration. ideally, the ai object would never be saved inside any IGameObject object. Maybe
	add a separate ai registrator and a function similar to init for ai.
* allow move_to steering with moving target.
* allow move_to steering with desired terminal velocity.
* improve precision of steering
* allow combination of multiple base moves in micro ai


\namespace game::ai
\brief namespace for classes and functions related to the artificial intelligence of
		units and squats.
\details For a detailed description of the architecture of the AI system, see \ref micro_ai
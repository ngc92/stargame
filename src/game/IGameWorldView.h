#ifndef IGAMEWORLDVIEW_H_INCLUDED
#define IGAMEWORLDVIEW_H_INCLUDED

#include "fwd.h"
#include "util.h"
#include "listener/listener.h"

namespace game
{
	class IGameViewModule;

	/*! \class IGameWorldView
		\brief Observer interface to the Game World.
		\details This class allows to observe the game world, i.e. set listeners
				and iterate over all objects.
	*/
	class IGameWorldView : noncopyable
	{
	public:
		virtual ~IGameWorldView() = default;

		/// gets the number of objects that are currently registered in the world.
		virtual std::size_t object_count() const = 0;

		/// adds a listener that is called whenever a new game objects is spawned in the world.
		virtual ListenerRef addSpawnListener(std::function<void(IGameObjectView&)> f) = 0;

		/// iterates over all game objects \p o inside this world and calls \p f(o).
		virtual void iterateAllObjects(const std::function<void(IGameObjectView&)>& f) const = 0;

		/// Adds a module to this worlds module list.
		/// the module is removed as soon as that weak_ptr
		/// expires.
		/// The module is directly initialized.
		virtual void addModule(std::weak_ptr<IGameViewModule> module) = 0;

	};
}

#endif // IGAMEWORLDVIEW_H_INCLUDED

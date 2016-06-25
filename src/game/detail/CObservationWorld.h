#ifndef CGAMEWORLD_H_INCLUDED
#define CGAMEWORLD_H_INCLUDED

#include "CWorldBase.h"

namespace game
{
	class ContactListener;

	class CObservationWorld : public CWorldBase
	{
	public:
		CObservationWorld();

		~CObservationWorld();

		/// perform a single step in the game simulation.
		void step( const spawn::ISpawnManager& spawner ) final;

		/// Adds a module to this worlds module list.
		/// the module is removed as soon as that weak_ptr
		/// expires.
		/// The module is directly initialized.
		void addModule(std::weak_ptr<IGameModule> module) final;
	private:
		std::unique_ptr<ContactListener> mContactListener;		//!< The contact listener for Box2D

		std::vector<std::weak_ptr<IGameModule>> mModules;			//! Vector of all registered game modules.

	};
}

#endif // CGAMEWORLD_H_INCLUDED

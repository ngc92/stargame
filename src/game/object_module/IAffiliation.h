#ifndef IAFFILIATION_H_INCLUDED
#define IAFFILIATION_H_INCLUDED

#include "common_includes.h"

namespace game
{
	class IAffiliation : public IGameObjectModule
	{
	public:
		/// gets the team of the object
		virtual int getTeam() const = 0;

		/// gets the owner of the object, i.e. the shooter in terms of missiles, bullets
		/// and the mothership in terms of smaller vessels etc.
		virtual const std::shared_ptr<IGameObjectView>& getOwner() const = 0;
	};
}

#endif // IAFFILIATION_H_INCLUDED

#ifndef CAFFILIATION_H_INCLUDED
#define CAFFILIATION_H_INCLUDED

#include "IAffiliation.h"
#include "property/TypedProperty.h"

namespace game
{
	template<class T>
	using Property = property::TypedProperty<T>;

	class CAffiliation : public IAffiliation, public ObjectCounter<CAffiliation>, public property::CPropertyObject
	{
	public:
		CAffiliation( int team, std::shared_ptr<IGameObjectView> owner = nullptr );
		CAffiliation( std::shared_ptr<IGameObjectView> owner );

		/// gets the team of the object
		int getTeam() const final;

		/// gets the owner of the object, i.e. the shooter in terms of missiles, bullets
		/// and the mothership in terms of smaller vessels etc.
		const std::shared_ptr<IGameObjectView>& getOwner() const final;

		// mandatory function that do nothing here
		void onInit( IGameObject& object, IGameWorld& world ) final {};
		void onStep( IGameObject& object, IGameWorld& world ) final {};

	private:
		Property<int> mTeam;

		std::shared_ptr<IGameObjectView> mOwner;
	};
}

#endif // CAFFILIATION_H_INCLUDED

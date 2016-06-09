#ifndef CTIMEDDELETION_H_INCLUDED
#define CTIMEDDELETION_H_INCLUDED

#include "ITimedDeletion.h"
#include "property/CPropertyObject.h"
#include "property/TypedProperty.h"

namespace game
{
	template<class T>
	using Property = property::TypedProperty<T>;

	class CTimedDeletion : public ITimedDeletion, public ObjectCounter<CTimedDeletion>, public property::CPropertyObject
	{
	public:
		CTimedDeletion( int lifetime );

		/// gets the scheduled time of deletion
		int getTotalLifetime() const final;

		/// gets the time of creation (of this timer)
		int getElapsedLifetime() const final;

		/// sets the time for scheduled deletion
		void setTotalLifetime( int dur ) final;

		/// initialise the module with the object.
		void onInit( IGameObject& object, IGameWorld& world );

		/// this function will be called every step by the game world, and should trigger
		/// the onStep listener.
		void onStep( IGameObject& object, IGameWorld& world);

	private:
		Property<int> mElapsedLifetime;
		Property<int> mTotalLifetime;
	};
}

#endif // CTIMEDDELETION_H_INCLUDED

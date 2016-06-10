#ifndef ITIMEDDELETION_H_INCLUDED
#define ITIMEDDELETION_H_INCLUDED

#include "common_includes.h"

namespace game
{
	class ITimedDeletion : public IGameObjectModule
	{
	public:
		/// gets the scheduled time of deletion
		virtual int getTotalLifetime() const = 0;

		/// gets the time of creation (of this timer)
		virtual int getElapsedLifetime() const = 0;

		/// sets the time for scheduled deletion
		virtual void setTotalLifetime( int Tdel ) = 0;

		/// sets the lifetime relative to now
		void setRemainingLifetime( int dur )
		{
			setTotalLifetime( getElapsedLifetime() + dur );
		}

		/// get the remaining lifetime
		int getRemainingLifetime() const
		{
			return getTotalLifetime() - getElapsedLifetime();
		}
	};
}

#endif // ITIMEDDELETION_H_INCLUDED

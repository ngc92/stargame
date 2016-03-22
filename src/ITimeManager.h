#ifndef ITIMEMANAGER_H_INCLUDED
#define ITIMEMANAGER_H_INCLUDED

#include "util.h"

/*! \class ITimeManager
	\brief Manages timing of frames
	\details This class's purpose is to ensure a constant framerate.
	\todo add more timing functionality.
*/
class ITimeManager: public ObjectCounter<ITimeManager>
{
	public:
		virtual ~ITimeManager() noexcept {};

		/// set target FPS
		virtual void setDesiredFPS(int fps) = 0;
		/// get target FPS
		virtual int getDesiredFPS() const = 0;

		/// wait until it's time for the next frame
		virtual bool waitTillNextFrame() = 0;
};

#endif // ITIMEMANAGER_H_INCLUDED

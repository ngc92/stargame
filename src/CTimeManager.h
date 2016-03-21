#ifndef CTIMEMANAGER_H_INCLUDED
#define CTIMEMANAGER_H_INCLUDED

#include "ITimeManager.h"
#include <chrono>

class CTimeManager : public ITimeManager
{
	public:
		CTimeManager();
		~CTimeManager() noexcept override{};

		void setDesiredFPS(int fps) override;
		int getDesiredFPS() const override;

		bool waitTillNextFrame() override;

	private:
		typedef std::chrono::high_resolution_clock clock;
		typedef clock::time_point time_point;

		int mDesiredFPS;
		int mFrameCount;
		time_point mLastFrameTime;
		time_point mNextFrameTime;
		time_point mStartTime;
};


#endif // CTIMEMANAGER_H_INCLUDED

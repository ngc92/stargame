#include "CTimeManager.h"
#include <thread>

CTimeManager::CTimeManager() : mDesiredFPS(50)
{
	mStartTime = clock::now();
	mNextFrameTime = mStartTime;
}

void CTimeManager::setDesiredFPS(int fps)
{
	mDesiredFPS = fps;
}

int CTimeManager::getDesiredFPS() const
{
	return mDesiredFPS;
}

bool CTimeManager::waitTillNextFrame()
{
	// check if we have to wait for the next frame
	if( clock::now() < mNextFrameTime)
	{
		std::this_thread::sleep_until(mNextFrameTime);
	}
	// if we have to catch up, (maybe because of one longer frame)
	/* else
	{

	}*/

	mFrameCount++;
	//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - mStartTime).count() / mFrameCount << "\n";
	mNextFrameTime += std::chrono::milliseconds(1000 / mDesiredFPS);
	mLastFrameTime = clock::now();

	// if the programme is slowed down significantly for a single frame, the best course of action is to
	// ignore that and continue with steady fps
	if( mLastFrameTime > mNextFrameTime )
	{
		mFrameCount = 0;
		mStartTime = mLastFrameTime;
		mNextFrameTime = mLastFrameTime + std::chrono::milliseconds(1000 / mDesiredFPS);
//		std::cout << "HANG\n";
	}
	return false;
}

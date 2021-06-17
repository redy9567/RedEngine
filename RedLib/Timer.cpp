#include "Timer.h"

#ifdef _WIN32
#include "Windows.h"
#elif __linux__
#include "unistd.h"
#endif

using namespace std;

Timer::Timer()
	:mElapsedTime(0.0)
	, mPaused(true)
{
	
}

Timer::~Timer()
{
	std::chrono::system_clock;
}

void Timer::start()
{
	mElapsedTime = 0.0;

	togglePause();
}

void Timer::stop()
{
	if(!mPaused)
	{
		mPaused = true;
		mEndTime = chrono::steady_clock::now();
		chrono::nanoseconds diff = (mEndTime - mStartTime);
		mElapsedTime += chrono::duration_cast<chrono::seconds>(diff).count();
	}
	
}

void Timer::togglePause()
{
	if (!mPaused)
	{
		mPaused = true;
		mEndTime = chrono::steady_clock::now();
		chrono::nanoseconds diff = (mEndTime - mStartTime);
		mElapsedTime += chrono::duration_cast<chrono::seconds>(diff).count();
	}
	else
	{
		mPaused = false;
		mStartTime = chrono::steady_clock::now();
	}
}

double Timer::getElapsedTime() const
{
	if (mPaused)
	{
		return mElapsedTime;
	}
	else
	{
		std::chrono::steady_clock::time_point currentTime;
		currentTime = chrono::steady_clock::now();
		chrono::nanoseconds diff = (currentTime - mStartTime);
		return chrono::duration_cast<chrono::seconds>(diff).count();
	}
}

#ifdef _WIN32
void Timer::sleepUntilElapsed(double ms)
{
	std::chrono::steady_clock::time_point currentTime, lastTime;
	currentTime = std::chrono::steady_clock::now();
	chrono::nanoseconds diff = (currentTime - mStartTime);
	double timeToSleep = ms - chrono::duration_cast<chrono::milliseconds>(diff).count();
	
	while (timeToSleep > 0.0)
	{
		lastTime = currentTime;
		currentTime = std::chrono::steady_clock::now();
		diff = (currentTime - lastTime);
		double timeElapsed = chrono::duration_cast<chrono::milliseconds>(diff).count();
		timeToSleep -= timeElapsed;
		if (timeToSleep > 10.0)
		{
			Sleep(10);
		}
	}
}
#elif __linux__
void Timer::sleepUntilElapsed(double ms)
{
	std::chrono::steady_clock::time_point currentTime, lastTime;
	currentTime = std::chrono::steady_clock::now();
	chrono::nanoseconds diff = (currentTime - mStartTime);
	double timeToSleep = ms - chrono::duration_cast<chrono::milliseconds>(diff).count();
	
	while (timeToSleep > 0.0)
	{
		lastTime = currentTime;
		currentTime = std::chrono::steady_clock::now();
		diff = (currentTime - lastTime);
		double timeElapsed = chrono::duration_cast<chrono::milliseconds>(diff).count();
		timeToSleep -= timeElapsed;
		if (timeToSleep > 10.0)
		{
			sleep(10);
		}
	}
}
#endif
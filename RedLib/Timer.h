//Inspired by Dean Lawson, Champlain College

#pragma once
#include "Trackable.h"
#include <chrono>

class Timer :public Trackable
{
public:
	Timer();
	~Timer();

	void start();
	void stop();
	double getElapsedTime() const;
	void sleepUntilElapsed(double ms);
	void togglePause();

private:
	std::chrono::steady_clock::time_point mStartTime;
	std::chrono::steady_clock::time_point mEndTime;
	double mElapsedTime;
	bool mPaused;

};
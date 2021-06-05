//Inspired by Dean Lawson, Champlain College

#pragma once
#include "Trackable.h"

struct LARGE_INTEGER;

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
	LARGE_INTEGER mStartTime;
	LARGE_INTEGER mEndTime;
	LARGE_INTEGER mTimerFrequency;
	double mElapsedTime;
	bool mPaused;

	//takes into account timer frequency
	double calcDifferenceInMS(LARGE_INTEGER from, LARGE_INTEGER to) const;

};
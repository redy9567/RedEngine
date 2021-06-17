#pragma once
#include "Trackable.h"

class Sprite;

class Animation : public Trackable
{

public:
	Animation(Sprite* frames, int numOfFrames, int fps);
	~Animation();

	void update(double deltaTime);

private:
	Animation() = delete;

	Sprite* mFrames;
	int mNumOfFrames;
	int mCurrentFrame;
	bool mOwnsSprites;
	
	int mFPS;
	double mTimePerFrame;
	double mTimer;

};

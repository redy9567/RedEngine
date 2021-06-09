#include "Animation.h"
#include "Sprite.h"

Animation::Animation(Sprite* frames, int numOfFrames, int fps)
{
	mFrames = frames;
	mNumOfFrames = numOfFrames;
	mCurrentFrame = 0;
	mOwnsSprites = false;

	mFPS = fps;
	mTimePerFrame = 1.0 / fps;
	mTimer = 0.0;
}

Animation::~Animation()
{
	if (mOwnsSprites)
	{
		delete[] mFrames;
		mFrames = nullptr;
	}
}

void Animation::update(double deltaTime)
{
	mTimer += deltaTime;
	if (mTimer >= mTimePerFrame)
	{
		mTimer -= mTimePerFrame;
		
		mCurrentFrame++;
		if (mCurrentFrame >= mNumOfFrames)
		{
			mCurrentFrame = 0;
		}
	}
}
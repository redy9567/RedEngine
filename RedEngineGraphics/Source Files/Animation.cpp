#include "Animation.h"
#include "AnimationData.h"
#include "Sprite.h"

Animation::Animation(AnimationData* data, int mFPS, bool isLooping)
{
	mData = data;
	setFPS(mFPS);
	mCurrentFrame = 0;
	mTimer = 0.0f;
	mIsLooping = isLooping;
	mIsDone = false;
}

Animation::~Animation()
{
	mData = nullptr;
}

void Animation::setFPS(int fps)
{
	mTimePerFrame = 1.0f / fps;
}

void Animation::update(float deltaTime)
{
	if (!mIsDone)
	{
		mTimer += deltaTime;

		while (mTimer > mTimePerFrame)
		{
			mCurrentFrame++;
			mTimer -= mTimePerFrame;
		}

		if (mData->mCount != 0)
		{
			if (mIsLooping)
				while (mCurrentFrame >= mData->mCount)
					mCurrentFrame -= mData->mCount;
			else
				if (mCurrentFrame >= mData->mCount)
				{
					mCurrentFrame--;
					mIsDone = true;
				}
					
		}
	}
	
		
}

Sprite* Animation::getCurrentSprite()
{
	return mData->getSprite(mCurrentFrame);
}
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
	mIsReversed = false;
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

		if (!mIsReversed)
		{
			while (mTimer > mTimePerFrame)
			{
				if(mCurrentFrame < mData->mCount)
					mCurrentFrame++;
				mTimer -= mTimePerFrame;
			}

			if (mData->mCount != 0)
			{
				if (mIsLooping)
					while (mCurrentFrame >= mData->mCount)
						mCurrentFrame -= mData->mCount;
				else
					if (mCurrentFrame == mData->mCount-1)
					{
						mIsDone = true;
					}

			}
		}
		else
		{
			while (mTimer > mTimePerFrame)
			{
				if(mCurrentFrame > 0)
					mCurrentFrame--;
				mTimer -= mTimePerFrame;
			}

			if (mData->mCount != 0)
			{
				if (mIsLooping)
					while (mCurrentFrame <= 0)
						mCurrentFrame += mData->mCount;
				else
					if (mCurrentFrame == 0)
					{
						mIsDone = true;
					}

			}
		}
		
	}
	
		
}

Sprite* Animation::getCurrentSprite()
{
	return mData->getSprite(mCurrentFrame);
}

void Animation::setReversed(bool reversed)
{
	if (mIsReversed != reversed)
	{
		mIsReversed = reversed;
		mIsDone = false;
	}
}
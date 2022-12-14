#include "Animation.h"
#include "AnimationData.h"
#include "Sprite.h"

Animation::Animation(AnimationData* data, int mFPS)
{
	mData = data;
	setFPS(mFPS);
	mCurrentFrame = 0;
	mTimer = 0.0f;
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
	mTimer += deltaTime;

	while (mTimer > mTimePerFrame)
	{
		mCurrentFrame++;
		mTimer -= mTimePerFrame;
	}

	if(mData->mCount != 0)
		while (mCurrentFrame >= mData->mCount)
			mCurrentFrame -= mData->mCount;
}

Sprite* Animation::getCurrentSprite()
{
	return mData->getSprite(mCurrentFrame);
}
#pragma once
#include "Trackable.h"

class AnimationData;
class Sprite;

class Animation : public Trackable
{

public:
	friend class GraphicsSystem;
	friend class AnimationManager;

	void setFPS(int fps);

	void update(float deltaTime);

	bool getIsDone() { return mIsLooping ? false : mIsDone; }

private:
	Animation(AnimationData* data, int mFPS, bool isLooping = false);
	~Animation();

	Animation() = delete;

	Sprite* getCurrentSprite();

	AnimationData* mData;
	unsigned int mCurrentFrame;
	float mTimePerFrame;
	float mTimer;

	bool mIsLooping;
	bool mIsDone;

};
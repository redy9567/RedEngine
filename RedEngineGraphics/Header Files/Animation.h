#pragma once
#include "Trackable.h"

class AnimationData;
class Sprite;

class Animation : public Trackable
{

public:
	friend class GraphicsSystem;

	Animation(AnimationData* data, int mFPS);
	~Animation();

	void setFPS(int fps);

	void update(float deltaTime);

private:
	Animation() = delete;

	Sprite* getCurrentSprite();

	AnimationData* mData;
	unsigned int mCurrentFrame;
	float mTimePerFrame;
	float mTimer;

};
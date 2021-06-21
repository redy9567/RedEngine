#pragma once
#include "Trackable.h"
#include <vector>

class Sprite;
class GraphicsBuffer;
class AnimationData;

class Animation : public Trackable
{

public:
	Animation(AnimationData* data, int fps);
	~Animation();

	void update(double deltaTime);

	Sprite* getCurrentSprite();

private:
	Animation() = delete;

	AnimationData* mAnimData;
	int mCurrentFrame;
	
	int mFPS;
	double mTimePerFrame;
	double mTimer;

};

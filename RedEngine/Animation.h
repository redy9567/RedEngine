#pragma once
#include "Trackable.h"
#include <vector>

class Sprite;
class GraphicsBuffer;

class Animation : public Trackable
{

public:
	Animation(Sprite* frames, int numOfFrames, int fps);
	Animation(GraphicsBuffer* gb, int rows, int columns, int fps, float scale = 1.0f);
	~Animation();

	void update(double deltaTime);

	Sprite* getCurrentSprite();

private:
	Animation() = delete;

	std::vector<Sprite*> mSprites;
	int mCurrentFrame;
	bool mOwnsSprites;
	
	int mFPS;
	double mTimePerFrame;
	double mTimer;

};

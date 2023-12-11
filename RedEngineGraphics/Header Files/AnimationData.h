#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class Sprite;
class Texture2D;

class AnimationData : public Trackable
{

public:
	friend class Animation;
	friend class AnimationManager;

private:
	AnimationData(Texture2D** texture, int numHorizontal, int numVertical, Vector2D scale = Vector2D::One());
	~AnimationData();
	AnimationData() = delete;

	Sprite* getSprite(int index);
	unsigned int getCount() { return mCount; }

	Sprite** mSprites;
	unsigned int mCount;

};
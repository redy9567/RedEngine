#pragma once
#include "Trackable.h"
#include <string>
#include "GameObject2D.h"
#include "Filepaths.h"

class Sprite;
class Texture2D;
class AnimationData;

const float STARTING_MOVEMENT_TIMER = 3.0f;

const float MAXIMUM_MOVE_TIMER = 3.0f;
const float MINIMUM_MOVE_TIMER = 1.0f;

const float MOVEMENT_SPEED = 1.0f;

const float MAXIMUM_MOVE_DISTANCE = 100.0f;
const float MINIMUM_MOVE_DISTANCE = 20.0f;

const float MOVE_RANGE = MAXIMUM_MOVE_TIMER - MINIMUM_MOVE_TIMER;

class Chicken : public GameObject2D
{
public:
	Chicken(float timeToHatch, float timeToMaturity, Vector2D location = Vector2D::Zero());
	~Chicken();

	void update(float deltaTime);

	void onMouseClick();

	bool isEgg() { return mState == ChickenState::EGG; }

private:
	enum class ChickenState
	{
		EGG,
		CHICK,
		CHICKEN
	};

	void animate(float deltaTime);
	void move();

	ChickenState mState;

	Texture2D* mpEggTexture;
	Sprite* mpEggSprite;

	Texture2D* mpEggHatchingTexture;
	AnimationData* mpEggHatchingAnimationData;
	Animation* mpEggHatchingAnimation;

	Texture2D* mpChickGrowingTexture;
	AnimationData* mpChickGrowingAnimationData;
	Animation* mpChickGrowingAnimation;

	Texture2D* mpChickTexture;
	Sprite* mpChickSprite;

	Texture2D* mpChickenTexture;
	Sprite* mpChickenSprite;
	
	float mTimeToHatch = 0.0f;
	float mTimeToMaturity = 0.0f;
	float mLifeTime = 0.0f;

	float mMoveUpdateTimer = 0.0f;

	bool mIsMoving;
	Vector2D mMoveStart;
	Vector2D mMoveEnd;
};
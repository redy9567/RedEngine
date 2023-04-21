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

const float MOVEMENT_SPEED = 0.01f;

const float MAXIMUM_MOVE_DISTANCE = 1.0f;
const float MINIMUM_MOVE_DISTANCE = 0.25f;

const float MOVE_RANGE = MAXIMUM_MOVE_TIMER - MINIMUM_MOVE_TIMER;

const std::string CKN_EGG_KEY = "Egg";
const std::string CKN_HATCHING_KEY = "Hatching";
const std::string CKN_GROWING_KEY = "Growing";
const std::string CKN_CHICK_KEY = "Chick";
const std::string CKN_CHICKEN_KEY = "Chicken";
const std::string CKN_CHICK_WALKING_KEY = "ChickWalking";
const std::string CKN_CHICKEN_WALKING_KEY = "ChickenWalking";

class Chicken : public GameObject2D
{
public:
	Chicken(float timeToHatch, float timeToMaturity, float timeToDeath, Vector2D location = Vector2D::Zero());
	~Chicken();

	void update(float deltaTime);

	void onMouseClick();

	bool isEgg() { return mState == ChickenState::EGG; }

private:
	enum class ChickenState
	{
		EGG,
		EGG_HATCHING,
		CHICK,
		CHICK_WALKING,
		CHICK_GROWING,
		CHICKEN,
		CHICKEN_WALKING,
		DEAD
	};

	void updateAnimation(float deltaTime);
	void updateChickenState();
	void updateImage();
	void move();
	void updatePosition();

	void changeState(ChickenState state) { mState = state; mStateChanged = true; }

	void loadData();

	ChickenState mState;
	bool mStateChanged;
	
	float mTimeToHatch = 0.0f;
	float mTimeToMaturity = 0.0f;
	float mTimeToDeath = 0.0f;
	float mLifeTime = 0.0f;

	float mMoveUpdateTimer = 0.0f;

	bool mIsMoving;
	Vector2D mMoveStart;
	Vector2D mMoveEnd;
};
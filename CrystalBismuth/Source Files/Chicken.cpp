#include "Chicken.h"
#include "GraphicsSystem.h"
#include "Sprite.h"
#include "Texture2D.h"
#include "Animation.h"

const float pi = 3.14159265358979323846f;

Chicken::Chicken(float timeToHatch, float timeToMaturity, float timeToDeath, Vector2D location)
{
	loadData();

	mTimeToHatch = timeToHatch;
	mTimeToMaturity = timeToHatch + timeToMaturity;
	mTimeToDeath = timeToHatch + timeToMaturity + timeToDeath;

	mState = ChickenState::EGG;
	mDrawingMode = GameObject2D::SpriteMode;
	mImage.s = GraphicsSystem::getInstance()->getSprite(CKN_EGG_KEY);

	mLoc = location;
	mIsMoving = false;
	mStateChanged = false;

	mDebugMode = false;

	mMoveUpdateTimer = STARTING_MOVEMENT_TIMER;
}

Chicken::~Chicken()
{
	
}

void Chicken::loadData()
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	if (!gs->getSprite(CKN_EGG_KEY))
	{
		Texture2D* eggTexture = gs->createAndAddTexture2D(CKN_EGG_KEY, RESOURCES_DIRECTORY + EGG_DIRECTORY + EGG_FILENAME, true);
		Sprite* eggSprite = gs->createAndAddSprite(CKN_EGG_KEY, &eggTexture, Vector2D::Zero(), eggTexture->getSize());

		Texture2D* hatchingTexture = gs->createAndAddTexture2D(CKN_HATCHING_KEY, RESOURCES_DIRECTORY + EGG_DIRECTORY + ANIMATIONS_DIRECTORY + EGG_HATCHING_FILENAME, true);
		gs->createAndAddAnimationData(CKN_HATCHING_KEY, &hatchingTexture, 24, 1);
		gs->createAndAddAnimation(CKN_HATCHING_KEY, CKN_HATCHING_KEY, 24);

		Texture2D* growingTexture = gs->createAndAddTexture2D(CKN_GROWING_KEY, RESOURCES_DIRECTORY + CHICKS_DIRECTORY + ANIMATIONS_DIRECTORY + CHICK_GROWING_FILENAME, true);
		gs->createAndAddAnimationData(CKN_GROWING_KEY, &growingTexture, 36, 1);
		gs->createAndAddAnimation(CKN_GROWING_KEY, CKN_GROWING_KEY, 36);

		Texture2D* chickTexture = gs->createAndAddTexture2D(CKN_CHICK_KEY, RESOURCES_DIRECTORY + CHICKS_DIRECTORY + CHICK_FILENAME, true);
		gs->createAndAddSprite(CKN_CHICK_KEY, &chickTexture, Vector2D::Zero(), chickTexture->getSize());

		Texture2D* chickenTexture = gs->createAndAddTexture2D(CKN_CHICKEN_KEY, RESOURCES_DIRECTORY + CHICKENS_DIRECTORY + CHICKEN_FILENAME, true);
		gs->createAndAddSprite(CKN_CHICKEN_KEY, &chickenTexture, Vector2D::Zero(), chickenTexture->getSize());

		Texture2D* chickWalkingTexture = gs->createAndAddTexture2D(CKN_CHICK_WALKING_KEY, RESOURCES_DIRECTORY + CHICKS_DIRECTORY + ANIMATIONS_DIRECTORY + CHICK_WALKING_FILENAME, true);
		gs->createAndAddAnimationData(CKN_CHICK_WALKING_KEY, &chickWalkingTexture, 4, 1);
		gs->createAndAddAnimation(CKN_CHICK_WALKING_KEY, CKN_CHICK_WALKING_KEY, 8, true);

		Texture2D* chickenWalkingTexture = gs->createAndAddTexture2D(CKN_CHICKEN_WALKING_KEY, RESOURCES_DIRECTORY + CHICKENS_DIRECTORY + ANIMATIONS_DIRECTORY + CHICKEN_WALKING_FILENAME, true);
		gs->createAndAddAnimationData(CKN_CHICKEN_WALKING_KEY, &chickenWalkingTexture, 18, 1);
		gs->createAndAddAnimation(CKN_CHICKEN_WALKING_KEY, CKN_CHICKEN_WALKING_KEY, 18, true);
	}
	
}

void Chicken::update(float deltaTime)
{
	mLifeTime += deltaTime;

	updateAnimation(deltaTime);
	updateChickenState();
	if (mStateChanged)
	{
		updateImage();
		mStateChanged = false;
	}

	if (mIsMoving)
		updatePosition();

	if (!mDebugMode && (mState == ChickenState::CHICK || mState == ChickenState::CHICKEN))
	{
		mMoveUpdateTimer -= deltaTime;
		move();
	}
		
}

void Chicken::updateAnimation(float deltaTime)
{
	if (mDrawingMode == GameObject2D::AnimationMode)
	{
		GraphicsSystem* gs = GraphicsSystem::getInstance();
		Animation* anim;
		switch (mState)
		{
		case ChickenState::EGG_HATCHING:
			anim = gs->getAnimation(CKN_HATCHING_KEY);
			break;
		case ChickenState::CHICK_WALKING:
			anim = gs->getAnimation(CKN_CHICK_WALKING_KEY);
			break;
		case ChickenState::CHICK_GROWING:
			anim = gs->getAnimation(CKN_GROWING_KEY);
			break;
		case ChickenState::CHICKEN_WALKING:
			anim = gs->getAnimation(CKN_CHICKEN_WALKING_KEY);
			break;
		default:
			return;

		}
		anim->update(deltaTime);
	}
}

void Chicken::updateChickenState()
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	if (mState == ChickenState::EGG)
	{
		if (mLifeTime > mTimeToHatch)
		{
			changeState(ChickenState::EGG_HATCHING);
		}
	}
	else if (mState == ChickenState::EGG_HATCHING)
	{
		Animation* hatchingAnimation = gs->getAnimation(CKN_HATCHING_KEY);

		if (hatchingAnimation->getIsDone())
		{
			changeState(ChickenState::CHICK);
		}
	}
	else if (mState == ChickenState::CHICK)
	{
		if (mLifeTime > mTimeToMaturity)
		{
			changeState(ChickenState::CHICK_GROWING);
		}
	}
	else if (mState == ChickenState::CHICK_GROWING)
	{

		Animation* growingAnimation = gs->getAnimation(CKN_GROWING_KEY);

		if (growingAnimation->getIsDone())
		{
			changeState(ChickenState::CHICKEN);
			mStateChanged = true;
		}
	}
	else if (mState == ChickenState::CHICKEN)
	{
		if (mLifeTime > mTimeToDeath)
		{
			changeState(ChickenState::DEAD);
		}
	}
}

void Chicken::updatePosition()
{
	
	if ((mMoveEnd - mLoc).length() < ((mMoveEnd - mMoveStart).normalized() * MOVEMENT_SPEED).length())
	{
		mIsMoving = false;
		mLoc = mMoveEnd;

		switch (mState)
		{
		case ChickenState::CHICK_WALKING:
			changeState(ChickenState::CHICK);
			break;
		case ChickenState::CHICKEN_WALKING:
			changeState(ChickenState::CHICKEN);
			break;
		}
	}
	else
	{
		mLoc += (mMoveEnd - mMoveStart).normalized() * MOVEMENT_SPEED;
	}
}

void Chicken::move() //Maybe move animation/sprite changes into it's own function??
{
	if (mMoveUpdateTimer <= 0.0f)
	{
		float randomAngle = ((float)rand() / (float)RAND_MAX) * 2 * pi;
		Vector2D dir = Vector2D(cos(randomAngle), sin(randomAngle));

		float randomDistance = ((float)rand() / (float)RAND_MAX * (MAXIMUM_MOVE_DISTANCE - MINIMUM_MOVE_DISTANCE)) + MINIMUM_MOVE_DISTANCE;

		mMoveStart = mLoc;
		mMoveEnd = mLoc + dir * randomDistance;
		mIsMoving = true;

		mMoveUpdateTimer = (((float)rand() / (float)RAND_MAX) * MOVE_RANGE) + MINIMUM_MOVE_TIMER;

		switch (mState)
		{
		case ChickenState::CHICK:
			changeState(ChickenState::CHICK_WALKING);
			break;
		case ChickenState::CHICKEN:
			changeState(ChickenState::CHICKEN_WALKING);
			break;
		}
	}
}

void Chicken::onMouseClick()
{
	mLifeTime += 1.0f;
}

void Chicken::updateImage()
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	switch (mState)
	{
	case ChickenState::EGG:
		mDrawingMode = GameObject2D::SpriteMode;
		mImage.s = gs->getSprite(CKN_EGG_KEY);
		break;
	case ChickenState::EGG_HATCHING:
		mDrawingMode = GameObject2D::AnimationMode;
		mImage.a = gs->getAnimation(CKN_HATCHING_KEY);
		break;
	case ChickenState::CHICK:
		mDrawingMode = GameObject2D::SpriteMode;
		mImage.s = gs->getSprite(CKN_CHICK_KEY);
		break;
	case ChickenState::CHICK_GROWING:
		mDrawingMode = GameObject2D::AnimationMode;
		mImage.a = gs->getAnimation(CKN_GROWING_KEY);
		break;
	case ChickenState::CHICKEN:
		mDrawingMode = GameObject2D::SpriteMode;
		mImage.s = gs->getSprite(CKN_CHICKEN_KEY);
		break;
	case ChickenState::CHICK_WALKING:
		mDrawingMode = GameObject2D::AnimationMode;
		mImage.a = GraphicsSystem::getInstance()->getAnimation(CKN_CHICK_WALKING_KEY);
		break;
	case ChickenState::CHICKEN_WALKING:
		mDrawingMode = GameObject2D::AnimationMode;
		mImage.a = GraphicsSystem::getInstance()->getAnimation(CKN_CHICKEN_WALKING_KEY);
		break;
	case ChickenState::DEAD:
		mDrawingMode = GameObject2D::None;
		mImage.a = nullptr;
		break;
	}
}

void Chicken::moveToLocation(Vector2D location)
{
	if (mDebugMode && (mState == ChickenState::CHICK || mState == ChickenState::CHICKEN || mState == ChickenState::CHICK_WALKING || mState == ChickenState::CHICKEN_WALKING))
	{
		mMoveStart = mLoc;
		mMoveEnd = location;
		mIsMoving = true;

		mMoveUpdateTimer = DEBUG_MOVE_TIMER;

		switch (mState)
		{
		case ChickenState::CHICK:
			changeState(ChickenState::CHICK_WALKING);
			break;
		case ChickenState::CHICKEN:
			changeState(ChickenState::CHICKEN_WALKING);
			break;
		}
	}
}
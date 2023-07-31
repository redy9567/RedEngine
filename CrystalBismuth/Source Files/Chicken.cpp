#include "Chicken.h"
#include "GraphicsSystem.h"
#include "Sprite.h"
#include "Texture2D.h"
#include "Animation.h"
#include "ChickenManager.h"

const float pi = 3.14159265358979323846f;

Chicken::Chicken(float timeToHatch, float timeToMaturity, float timeToDeath, ChickenColor color, Vector2D location)
{
	loadData();

	mTimeToHatch = timeToHatch * GetHatchModifier(color);
	mTimeToMaturity = mTimeToHatch + timeToMaturity * GetGrowTimerModifier(color);
	mTimeToDeath = mTimeToHatch + mTimeToMaturity + timeToDeath;

	mState = ChickenState::EGG;
	mDrawingMode = GameObject2D::SpriteMode;
	mImage.s = GraphicsSystem::getInstance()->getSprite(CKN_EGG_KEY);

	updateProperties(color);

	mLoc = location;
	mIsMoving = false;
	mStateChanged = false;

	mDebugMode = false;

	mIsEvolved = false;

	mMoveUpdateTimer = STARTING_MOVEMENT_TIMER;
}

Chicken::Chicken(float timeToHatch, float timeToMaturity, float timeToDeath, ChickenProperties properties, Vector2D location)
{
	loadData();

	mTimeToHatch = timeToHatch * properties.hatchModifier;
	mTimeToMaturity = mTimeToHatch + timeToMaturity * properties.hatchModifier;
	mTimeToDeath = mTimeToHatch + mTimeToMaturity + timeToDeath;

	mState = ChickenState::EGG;
	mDrawingMode = GameObject2D::SpriteMode;
	mImage.s = GraphicsSystem::getInstance()->getSprite(CKN_EGG_KEY);

	mProperties = properties;

	mLoc = location;
	mIsMoving = false;
	mStateChanged = false;

	mDebugMode = false;

	mMoveUpdateTimer = STARTING_MOVEMENT_TIMER;
}

Chicken::Chicken(ChickenProperties properties, Vector2D location)
{
	loadData();

	mTimeToHatch = 0.0f;
	mTimeToMaturity = 0.0f;
	mTimeToDeath = 0.0f;

	mState = ChickenState::INFERTILE_EGG;
	mDrawingMode = GameObject2D::SpriteMode;
	mImage.s = GraphicsSystem::getInstance()->getSprite(CKN_EGG_KEY);

	mProperties = properties;

	mLoc = location;
	mIsMoving = false;
	mStateChanged = false;

	mDebugMode = false;

	mMoveUpdateTimer = STARTING_MOVEMENT_TIMER;
}

Chicken::~Chicken()
{
	if (mDrawingMode == AnimationMode)
		GraphicsSystem::getInstance()->removeAndDeleteAnimation(mImage.a);
}

void Chicken::loadData()
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	if (!gs->getSprite(CKN_EGG_KEY))
	{
		Texture2D* eggTexture = gs->createAndAddTexture2D(CKN_EGG_KEY, RESOURCES_DIRECTORY + EGG_DIRECTORY + EGG_FILENAME, true);
		Sprite* eggSprite = gs->createAndAddSprite(CKN_EGG_KEY, &eggTexture, Vector2D::Zero(), eggTexture->getSize());

		Texture2D* hatchingTexture = gs->createAndAddTexture2D(CKN_HATCHING_KEY, RESOURCES_DIRECTORY + EGG_DIRECTORY + ANIMATIONS_DIRECTORY + EGG_HATCHING_FILENAME, true);
		gs->createAndAddAnimationData(CKN_HATCHING_KEY, &hatchingTexture, 24, 1, Vector2D(2));

		Texture2D* growingTexture = gs->createAndAddTexture2D(CKN_GROWING_KEY, RESOURCES_DIRECTORY + CHICKS_DIRECTORY + ANIMATIONS_DIRECTORY + CHICK_GROWING_FILENAME, true);
		gs->createAndAddAnimationData(CKN_GROWING_KEY, &growingTexture, 36, 1);

		Texture2D* chickTexture = gs->createAndAddTexture2D(CKN_CHICK_KEY, RESOURCES_DIRECTORY + CHICKS_DIRECTORY + CHICK_FILENAME, true);
		gs->createAndAddSprite(CKN_CHICK_KEY, &chickTexture, Vector2D::Zero(), chickTexture->getSize());

		Texture2D* chickenTexture = gs->createAndAddTexture2D(CKN_CHICKEN_KEY, RESOURCES_DIRECTORY + CHICKENS_DIRECTORY + CHICKEN_FILENAME, true);
		gs->createAndAddSprite(CKN_CHICKEN_KEY, &chickenTexture, Vector2D::Zero(), chickenTexture->getSize());

		Texture2D* chickWalkingTexture = gs->createAndAddTexture2D(CKN_CHICK_WALKING_KEY, RESOURCES_DIRECTORY + CHICKS_DIRECTORY + ANIMATIONS_DIRECTORY + CHICK_WALKING_FILENAME, true);
		gs->createAndAddAnimationData(CKN_CHICK_WALKING_KEY, &chickWalkingTexture, 4, 1);

		Texture2D* chickenWalkingTexture = gs->createAndAddTexture2D(CKN_CHICKEN_WALKING_KEY, RESOURCES_DIRECTORY + CHICKENS_DIRECTORY + ANIMATIONS_DIRECTORY + CHICKEN_WALKING_FILENAME, true);
		gs->createAndAddAnimationData(CKN_CHICKEN_WALKING_KEY, &chickenWalkingTexture, 18, 1);

		Texture2D* chickenDeathTexture = gs->createAndAddTexture2D(CKN_CHICKEN_DEATH_KEY, RESOURCES_DIRECTORY + CHICKENS_DIRECTORY + ANIMATIONS_DIRECTORY + CHICKEN_DEATH_FILENAME, true);
		gs->createAndAddAnimationData(CKN_CHICKEN_DEATH_KEY, &chickenDeathTexture, 43, 1);

		Texture2D* chickChaoGrowTexture = gs->createAndAddTexture2D(CKN_CHICK_CHAO_GROW_KEY, RESOURCES_DIRECTORY + CHICKS_DIRECTORY + ANIMATIONS_DIRECTORY + CHICK_CHAO_GROW_FILENAME, true);
		gs->createAndAddAnimationData(CKN_CHICK_CHAO_GROW_KEY, &chickChaoGrowTexture, 59, 1);

		Texture2D* chickenBlackHoleTexture = gs->createAndAddTexture2D(CKN_CHICKEN_BLACKHOLE_DEATH_KEY, RESOURCES_DIRECTORY + CHICKENS_DIRECTORY + ANIMATIONS_DIRECTORY + CHICKEN_BLACKHOLE_DEATH_FILENAME, true);
		gs->createAndAddAnimationData(CKN_CHICKEN_BLACKHOLE_DEATH_KEY, &chickenBlackHoleTexture, 10, 1);

		Texture2D* ChickMorphTexture = gs->createAndAddTexture2D(CKN_MORPHING_KEY, RESOURCES_DIRECTORY + CHICKS_DIRECTORY + ANIMATIONS_DIRECTORY + CHICK_MORPH_FILENAME, true);
		gs->createAndAddAnimationData(CKN_MORPHING_KEY, &ChickMorphTexture, 58, 1);

		Texture2D* ChickFF7HatchTexture = gs->createAndAddTexture2D(CKN_CHICK_FF7_HATCH_KEY, RESOURCES_DIRECTORY + CHICKS_DIRECTORY + ANIMATIONS_DIRECTORY + CHICK_FF7HATCH_FILENAME, true);
		gs->createAndAddAnimationData(CKN_CHICK_FF7_HATCH_KEY, &ChickFF7HatchTexture, 35, 1);

		Texture2D* ChickenMagicCircleDeathTexture = gs->createAndAddTexture2D(CKN_FALL_INTO_CIRCLE_KEY, RESOURCES_DIRECTORY + CHICKENS_DIRECTORY + ANIMATIONS_DIRECTORY + CHICKEN_MAGIC_CIRCLE_FILENAME, true);
		gs->createAndAddAnimationData(CKN_FALL_INTO_CIRCLE_KEY, &ChickenMagicCircleDeathTexture, 49, 1);

		//Funky Chicken Evolution
		Texture2D* funkyChickenTexture = gs->createAndAddTexture2D(CKN_FUNKY_CHICKEN_KEY, FUNKY_CHICKEN_FILEPATH, true);
		gs->createAndAddSprite(CKN_FUNKY_CHICKEN_KEY, &funkyChickenTexture, Vector2D::Zero(), funkyChickenTexture->getSize());

		Texture2D* funkyChickenWalkingTexture = gs->createAndAddTexture2D(CKN_FUNKY_CHICKEN_WALKING_KEY, FUNKY_CHICKEN_WALKING_FILEPATH, true);
		gs->createAndAddAnimationData(CKN_FUNKY_CHICKEN_WALKING_KEY, &funkyChickenWalkingTexture, 20, 1);
	}
	
}

void Chicken::update(float deltaTime)
{
	mLifeTime += deltaTime;

	if (mState == ChickenState::CHICKEN || mState == ChickenState::CHICKEN_WALKING)
	{
		if (mFertileTimer > 0.0f)
		{
			mFertileTimer -= deltaTime;
			if (mFertileTimer <= 0.0f)
				mIsFertile = true;
		}

		if (mBreedingTimer > 0.0f)
			mBreedingTimer -= deltaTime;

		if (mEggLayingTimer > 0.0f)
			mEggLayingTimer -= deltaTime;
		else
			layEgg();
	}

	updateAnimation(deltaTime);
	updateChickenState();

	if (mIsMoving)
		updatePosition();

	if (!mDebugMode && (mState == ChickenState::CHICK || mState == ChickenState::CHICKEN))
	{
		mMoveUpdateTimer -= deltaTime;
		move();
	}

	if (mStateChanged)
	{
		updateImage();
		mStateChanged = false;
	}
		
}

void Chicken::updateAnimation(float deltaTime)
{
	if (mDrawingMode == GameObject2D::AnimationMode)
	{
		mImage.a->update(deltaTime);
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
		Animation* hatchingAnimation = mImage.a;

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

		Animation* growingAnimation = mImage.a;

		if (growingAnimation->getIsDone())
		{
			changeState(ChickenState::CHICKEN);
			mEggLayingTimer = EGG_LAYING_TIMER;
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

	int RandomNumber;

	switch (mState)
	{
	case ChickenState::EGG:
		mDrawingMode = GameObject2D::SpriteMode;
		mImage.s = gs->getSprite(CKN_EGG_KEY);
		break;
	case ChickenState::EGG_HATCHING:
		mDrawingMode = GameObject2D::AnimationMode;
		RandomNumber = rand() % 2;
		if (RandomNumber == 0)
		{
			mImage.a = gs->createAndAddAnimation(CKN_HATCHING_KEY, 24);
		}
		else if (RandomNumber == 1)
		{
			mImage.a = gs->createAndAddAnimation(CKN_CHICK_FF7_HATCH_KEY, 8);
		}
		break;
	case ChickenState::CHICK:
		mDrawingMode = GameObject2D::SpriteMode;
		mImage.s = gs->getSprite(CKN_CHICK_KEY);
		break;
	case ChickenState::CHICK_GROWING:
		mDrawingMode = GameObject2D::AnimationMode;
		RandomNumber = rand() % 3;
		if (RandomNumber == 0)
		{
			mImage.a = gs->createAndAddAnimation(CKN_GROWING_KEY, 36);
		}
		else if (RandomNumber == 1)
		{
			mImage.a = gs->createAndAddAnimation(CKN_CHICK_CHAO_GROW_KEY, 8);
		}
		else
		{
			mImage.a = gs->createAndAddAnimation(CKN_MORPHING_KEY, 13);
		}
		break;
		
	case ChickenState::CHICKEN:
		mDrawingMode = GameObject2D::SpriteMode;
		mImage.s = mIsEvolved ? gs->getSprite(CKN_FUNKY_CHICKEN_KEY) : gs->getSprite(CKN_CHICKEN_KEY);
		break;
	case ChickenState::CHICK_WALKING:
		mDrawingMode = GameObject2D::AnimationMode;
		mImage.a = gs->createAndAddAnimation(CKN_CHICK_WALKING_KEY, 8, true);
		break;
	case ChickenState::CHICKEN_WALKING:
		mDrawingMode = GameObject2D::AnimationMode;
		mImage.a = mIsEvolved ? gs->createAndAddAnimation(CKN_FUNKY_CHICKEN_WALKING_KEY, 18, true) : gs->createAndAddAnimation(CKN_CHICKEN_WALKING_KEY, 18, true);
		break;
	case ChickenState::DEAD:
		mDrawingMode = GameObject2D::AnimationMode;
		RandomNumber = rand() % 3;
		if (RandomNumber == 0)
		{
			mImage.a = gs->createAndAddAnimation(CKN_CHICKEN_DEATH_KEY, 18);
		}
		else if (RandomNumber == 1)
		{
			mImage.a = gs->createAndAddAnimation(CKN_CHICKEN_BLACKHOLE_DEATH_KEY, 5);
		}
		else
		{
			mImage.a = gs->createAndAddAnimation(CKN_FALL_INTO_CIRCLE_KEY, 12);
		}
			break;
	}
}

void Chicken::moveToLocation(Vector2D location)
{
	if ((mState == ChickenState::CHICK || mState == ChickenState::CHICKEN || mState == ChickenState::CHICK_WALKING || mState == ChickenState::CHICKEN_WALKING))
	{
		mMoveStart = mLoc;
		mMoveEnd = location;
		mIsMoving = true;

		mMoveUpdateTimer = MAXIMUM_MOVE_TIMER;

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

float Chicken::GetBreedingModifier(ChickenColor color)
{
	switch (color)
	{
	case ChickenColor::WHITE:
		return 1.0f;

	case ChickenColor::BLACK:
		return 1.0f;

	case ChickenColor::BLUE:
		return 1.04f;

	case ChickenColor::LIGHT_BLUE:
		return 1.0f;

	case ChickenColor::GREEN:
		return 1.03f;

	case ChickenColor::YELLOW:
		return 0.97f;

	case ChickenColor::RED:
		return 1.0f;

	case ChickenColor::PURPLE:
		return 1.02f;

	default:
		return 0.0f;
	}
}

float Chicken::GetHatchModifier(ChickenColor color)
{
	switch (color)
	{
	case ChickenColor::WHITE:
		return 1.0f;

	case ChickenColor::BLACK:
		return 1.04f;

	case ChickenColor::BLUE:
		return 1.0f;

	case ChickenColor::LIGHT_BLUE:
		return 0.94f;

	case ChickenColor::GREEN:
		return 1.0f;

	case ChickenColor::YELLOW:
		return 1.03f;

	case ChickenColor::RED:
		return 1.03f;

	case ChickenColor::PURPLE:
		return 1.02f;

	default:
		return 0.0f;
	}
}

float Chicken::GetEggLayingModifier(ChickenColor color)
{
	switch (color)
	{
	case ChickenColor::WHITE:
		return 1.0f;

	case ChickenColor::BLACK:
		return 1.0f;

	case ChickenColor::BLUE:
		return 0.96f;

	case ChickenColor::LIGHT_BLUE:
		return 1.06f;

	case ChickenColor::GREEN:
		return 0.94f;

	case ChickenColor::YELLOW:
		return 1.0f;

	case ChickenColor::RED:
		return 1.06f;

	case ChickenColor::PURPLE:
		return 1.02f;

	default:
		return 0.0f;
	}
}

float Chicken::GetGrowTimerModifier(ChickenColor color)
{
	switch (color)
	{
	case ChickenColor::WHITE:
		return 1.0f;

	case ChickenColor::BLACK:
		return 0.96f;

	case ChickenColor::BLUE:
		return 1.0f;

	case ChickenColor::LIGHT_BLUE:
		return 1.0f;

	case ChickenColor::GREEN:
		return 1.03f;

	case ChickenColor::YELLOW:
		return 0.94f;

	case ChickenColor::RED:
		return 0.97f;

	case ChickenColor::PURPLE:
		return 1.02f;

	default:
		return 0.0f;
	}
}

Vector3D Chicken::GetChickenColor(ChickenColor color)
{
	//I think it would be really cool to add a programatically converted Color Code -> Vector3D

	switch (color)
	{
	case ChickenColor::WHITE:
		return Vector3D(1.0f, 1.0f, 1.0f);

	case ChickenColor::BLACK:
		return Vector3D(0.5f, 0.5f, 0.5f);

	case ChickenColor::BLUE:
		return Vector3D(0.55f, 0.67f, 1.0f);

	case ChickenColor::LIGHT_BLUE:
		return Vector3D(0.55f, 1.0f, 0.97f);

	case ChickenColor::GREEN:
		return Vector3D(0.44f, 1.0f, 0.44f);

	case ChickenColor::YELLOW:
		return Vector3D(1.0f, 0.95f, 0.44f);

	case ChickenColor::RED:
		return Vector3D(1.0f, 0.44f, 0.44f);

	case ChickenColor::PURPLE:
		return Vector3D(0.79f,  0.42f, 1.0f);

	default:
		return Vector3D::Zero();
	}
}

void Chicken::changeState(ChickenState state)
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	if (mDrawingMode == GameObject2D::AnimationMode)
		gs->removeAndDeleteAnimation(mImage.a);
		
	mState = state; 
	mStateChanged = true;
}

void Chicken::updateProperties(ChickenColor color)
{
	mProperties.breedingModifier = GetBreedingModifier(color);
	mProperties.eggLayingModifier = GetEggLayingModifier(color);
	mProperties.growTimerModifier = GetGrowTimerModifier(color);
	mProperties.hatchModifier = GetHatchModifier(color);

	mProperties.chickenColor = GetChickenColor(color);

	mProperties.breedingGeneStrength = rand() % 10 + 1;
	mProperties.eggLayingGeneStrength = rand() % 10 + 1;
	mProperties.growTimerGeneStrength = rand() % 10 + 1;
	mProperties.hatchGeneStrength = rand() % 10 + 1;
	mProperties.colorGeneStrength = rand() % 10 + 1;
}

void Chicken::layEgg()
{
	mEggLayingTimer = EGG_LAYING_TIMER;
	ChickenManager* cm = ChickenManager::getInstance();

	if (mIsFertile)
		cm->createAndAddChicken(mFertileProperties, mLoc);
	else
		cm->createUnfertileEgg(mProperties, mLoc);

	mIsFertile = false;
}

void Chicken::fertilize(ChickenProperties babyProperties, float fertilizeTimer)
{
	if (mState == ChickenState::CHICKEN || mState == ChickenState::CHICKEN_WALKING)
	{
		mFertileTimer = fertilizeTimer;
		mFertileProperties = babyProperties;
		mIsFertile = true;

		mBreedingTimer = BREEDING_COOLDOWN;
	}
}

#include "Chicken.h"
#include "GraphicsSystem.h"
#include "Sprite.h"
#include "Texture2D.h"
#include "Animation.h"

#define _USE_MATH_DEFINES

const float pi = 3.14159265358979323846f;

Chicken::Chicken(float timeToHatch, float timeToMaturity, Vector2D location)
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	mpEggTexture = gs->createAndAddTexture2D("egg", RESOURCES_DIRECTORY + EGG_DIRECTORY + EGG_FILENAME, true);
	mpEggSprite = gs->createAndAddSprite("egg", &mpEggTexture, Vector2D::Zero(), mpEggTexture->getSize());

	mpEggHatchingTexture = gs->createAndAddTexture2D("eggHatching", RESOURCES_DIRECTORY + EGG_DIRECTORY + ANIMATIONS_DIRECTORY + EGG_HATCHING_FILENAME, true);
	mpEggHatchingAnimationData = gs->createAndAddAnimationData("eggHatching", &mpEggHatchingTexture, 24, 1);
	mpEggHatchingAnimation = gs->createAndAddAnimation("eggHatching", "eggHatching", 24);

	mpChickGrowingTexture = gs->createAndAddTexture2D("chickGrowing", RESOURCES_DIRECTORY + CHICKS_DIRECTORY + ANIMATIONS_DIRECTORY + CHICK_GROWING_FILENAME, true);
	mpChickGrowingAnimationData = gs->createAndAddAnimationData("chickGrowing", &mpChickGrowingTexture, 36, 1);
	mpChickGrowingAnimation = gs->createAndAddAnimation("chickGrowing", "chickGrowing", 36);

	mpChickTexture = gs->createAndAddTexture2D("chick", RESOURCES_DIRECTORY + CHICKS_DIRECTORY + CHICK_FILENAME, true);
	mpChickSprite = gs->createAndAddSprite("chick", &mpChickTexture, Vector2D::Zero(), mpChickTexture->getSize());

	mpChickenTexture = gs->createAndAddTexture2D("chicken", RESOURCES_DIRECTORY + CHICKENS_DIRECTORY + CHICKEN_FILENAME, true);
	mpChickenSprite = gs->createAndAddSprite("chicken", &mpChickenTexture, Vector2D::Zero(), mpChickenTexture->getSize());

	mTimeToHatch = timeToHatch;
	mTimeToMaturity = timeToHatch + timeToMaturity;

	mState = ChickenState::EGG;
	mDrawingMode = GameObject2D::SpriteMode;
	mImage.s = mpEggSprite;

	mLoc = location;

	mMoveUpdateTimer = 15.0f;
}

Chicken::~Chicken()
{
	
}

void Chicken::update(float deltaTime)
{
	mLifeTime += deltaTime;

	animate(deltaTime);

	mMoveUpdateTimer -= deltaTime;
	move();
		
	
}

void Chicken::animate(float deltaTime)
{
	if (mState == ChickenState::EGG)
	{
		if (mLifeTime > mTimeToHatch)
		{
			mDrawingMode = GameObject2D::AnimationMode;
			mImage.a = mpEggHatchingAnimation;

			mState = ChickenState::CHICK;
		}
	}
	else if (mState == ChickenState::CHICK)
	{
		if (mDrawingMode == GameObject2D::AnimationMode)
		{
			mpEggHatchingAnimation->update(deltaTime);

			if (mpEggHatchingAnimation->getIsDone())
			{
				mDrawingMode = GameObject2D::SpriteMode;
				mImage.s = mpChickSprite;
			}
		}
		else if (mLifeTime > mTimeToMaturity)
		{
			mImage.a = mpChickGrowingAnimation;
			mDrawingMode = GameObject2D::AnimationMode;
			mState = ChickenState::CHICKEN;
		}
	}
	else if (mState == ChickenState::CHICKEN)
	{
		if (mDrawingMode == GameObject2D::AnimationMode)
		{
			mpChickGrowingAnimation->update(deltaTime);

			if (mpChickGrowingAnimation->getIsDone())
			{
				mDrawingMode = GameObject2D::SpriteMode;
				mImage.s = mpChickenSprite;
			}
		}
	}
}

void Chicken::move()
{
	if (mMoveUpdateTimer <= 0.0f)
	{
		float randomAngle = ((float)rand() / (float)RAND_MAX) * 2 * pi;
		Vector2D dir = Vector2D(cos(randomAngle), sin(randomAngle));

		mLoc += dir * 20;

		mMoveUpdateTimer = ((float)rand() / (float)RAND_MAX) * 0.1f;
	}
}

void Chicken::onMouseClick()
{
	mLifeTime += 1.0f;
}
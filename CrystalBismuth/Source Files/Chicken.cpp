#include "Chicken.h"
#include "GraphicsSystem.h"
#include "Sprite.h"
#include "Texture2D.h"
#include "Animation.h"

Chicken::Chicken(float timeToHatch, float timeToMaturity)
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	mpEggTexture = new Texture2D(RESOURCES_DIRECTORY + EGG_DIRECTORY + EGG_FILENAME, true);
	mpEggSprite = gs->createAndAddSprite("egg", &mpEggTexture, Vector2D::Zero(), Vector2D(mpEggTexture->getWidth(), mpEggTexture->getHeight()));

	mpEggHatchingTexture = new Texture2D(RESOURCES_DIRECTORY + EGG_DIRECTORY + ANIMATIONS_DIRECTORY + EGG_HATCHING_FILENAME, true);
	mpEggHatchingAnimationData = gs->createAndAddAnimationData("eggHatching", &mpEggHatchingTexture, 24, 1);
	mpEggHatchingAnimation = gs->createAndAddAnimation("eggHatching", "eggHatching", 24);

	mpChickTexture = new Texture2D(RESOURCES_DIRECTORY + CHICKS_DIRECTORY + CHICK_FILENAME, true);
	mpChickSprite = gs->createAndAddSprite("chick", &mpChickTexture, Vector2D::Zero(), Vector2D(mpChickTexture->getWidth(), mpChickTexture->getHeight()));

	mpChickenTexture = new Texture2D(RESOURCES_DIRECTORY + CHICKENS_DIRECTORY + CHICKEN_FILENAME, true);
	mpChickenSprite = gs->createAndAddSprite("chicken", &mpChickenTexture, Vector2D::Zero(), Vector2D(mpChickenTexture->getWidth(), mpChickenTexture->getHeight()));

	mTimeToHatch = timeToHatch;
	mTimeToMaturity = timeToHatch + timeToMaturity;

	mDrawingMode = GameObject2D::SpriteMode;
	mImage.s = mpEggSprite;
	mHatched = false;
}

Chicken::~Chicken()
{
	delete mpEggTexture;
	delete mpEggHatchingTexture;
	delete mpChickTexture;
}

void Chicken::update(float deltaTime)
{
	mLifeTime += deltaTime;

	if (!mHatched)
	{
		if (mLifeTime > mTimeToHatch)
		{
			mDrawingMode = GameObject2D::AnimationMode;
			mImage.a = mpEggHatchingAnimation;

			mHatched = true;
		}
	}
	else
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
			mImage.s = mpChickenSprite;
		}

	}
		
	
}
#include "UIButton.h"
#include "GraphicsSystem.h"
#include "Animation.h"
#include "Texture2D.h"

using namespace std;

UIButton::UIButton(Vector2D location, bool codeAnimation)
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	if (codeAnimation)
	{
		mpTexture = gs->createAndAddTexture2D("uiButton", RESOURCES_DIRECTORY + UI_DIRECTORY + BUTTONS_DIRECTORY + SETTINGS_BUTTON_FILENAME, true);
		mpSprite = gs->createAndAddSprite("uiButton", &mpTexture, Vector2D::Zero(), mpTexture->getSize());
		mpAnimationData = nullptr;
		mpAnimation = nullptr;

		mDrawingMode = GameObject2D::SpriteMode;
		mImage.s = mpSprite;

		mLoc = location;
		mOrigLoc = location;
		mDistToMove = 20.0f;
	}
	else
	{
		mpTexture = gs->createAndAddTexture2D("uiButtonAnim", RESOURCES_DIRECTORY + UI_DIRECTORY + ANIMATIONS_DIRECTORY + BUTTONS_DIRECTORY + SETTINGS_BUTTON_ANIMATION_FILENAME, true);
		mpAnimationData = gs->createAndAddAnimationData("uiButtonAnim", &mpTexture, 9, 1);
		mpAnimation = gs->createAndAddAnimation("uiButtonAnim", "uiButtonAnim", 60);
		mpSprite = nullptr;

		mDrawingMode = GameObject2D::AnimationMode;
		mImage.a = mpAnimation;

		mLoc = location;
	}

	mIsHover = false;
}

UIButton::~UIButton()
{

}

void UIButton::update(float deltaTime)
{
	if (mDrawingMode == GameObject2D::AnimationMode)
	{
		mpAnimation->setReversed(!mIsHover);

		mpAnimation->update(deltaTime);
	}
	else
	{
		if (mIsHover && mLoc.getY() < mOrigLoc.getY() + mDistToMove)
		{
			mLoc.setY(mLoc.getY() + mDistToMove * deltaTime * 10);
		}
		else if (!mIsHover && mLoc.getY() > mOrigLoc.getY())
		{
			mLoc.setY(mLoc.getY() - mDistToMove * deltaTime * 10);
		}
	}
	
}
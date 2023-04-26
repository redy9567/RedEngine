#include "UIElement.h"
#include "GraphicsSystem.h"
#include "Animation.h"
#include "Texture2D.h"

using namespace std;

UIElement::UIElement(std::string spriteFilepath, std::string objectKey, Direction animationDirection, float distanceToMove, Vector2D location)
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	
	mpTexture = gs->createAndAddTexture2D(objectKey, spriteFilepath, true);
	mpSprite = gs->createAndAddSprite(objectKey, &mpTexture, Vector2D::Zero(), mpTexture->getSize());
	mpAnimationData = nullptr;
	mpAnimation = nullptr;

	mDrawingMode = GameObject2D::SpriteMode;
	mImage.s = mpSprite;

	mLoc = location;
	mOrigLoc = location;
	mDistToMove = distanceToMove;

	mIsHover = false;
	mAnimationDirection = animationDirection;
}

UIElement::UIElement(std::string animationTextureFilepath, std::string objectKey, int animationColumns, int animationRows, Vector2D location)
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	
	mpTexture = gs->createAndAddTexture2D(objectKey, animationTextureFilepath, true);
	mpAnimationData = gs->createAndAddAnimationData(objectKey, &mpTexture, animationColumns, animationRows);
	mpAnimation = gs->createAndAddAnimation(objectKey, objectKey, 60);
	mpSprite = nullptr;

	mDrawingMode = GameObject2D::AnimationMode;
	mImage.a = mpAnimation;
	mDistToMove = 0.0f;

	mLoc = location;
	mAnimationDirection = (Direction)-1;

	mIsHover = false;
}

UIElement::~UIElement()
{

}

void UIElement::update(float deltaTime)
{
	if (mDrawingMode == GameObject2D::AnimationMode)
	{
		mpAnimation->setReversed(!mIsHover);

		mpAnimation->update(deltaTime);
	}
	else
	{
		if (mAnimationDirection == Left)
		{
			if (mIsHover && mLoc.getX() > mOrigLoc.getX() - mDistToMove)
			{
				mLoc.setX(mLoc.getX() - mDistToMove * deltaTime * 10);
			}
			else if (!mIsHover && mLoc.getX() < mOrigLoc.getX())
			{
				mLoc.setX(mLoc.getX() + mDistToMove * deltaTime * 10);
			}
		}
		else if (mAnimationDirection == Right)
		{
			if (mIsHover && mLoc.getX() < mOrigLoc.getX() + mDistToMove)
			{
				mLoc.setX(mLoc.getX() + mDistToMove * deltaTime * 10);
			}
			else if (!mIsHover && mLoc.getX() > mOrigLoc.getX())
			{
				mLoc.setX(mLoc.getX() - mDistToMove * deltaTime * 10);
			}
		}
		else if (mAnimationDirection == Up)
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
		else if (mAnimationDirection == Down)
		{
			if (mIsHover && mLoc.getY() > mOrigLoc.getY() - mDistToMove)
			{
				mLoc.setY(mLoc.getY() - mDistToMove * deltaTime * 10);
			}
			else if (!mIsHover && mLoc.getY() < mOrigLoc.getY())
			{
				mLoc.setY(mLoc.getY() + mDistToMove * deltaTime * 10);
			}
		}
	}
	
}
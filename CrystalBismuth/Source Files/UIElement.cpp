#include "UIElement.h"
#include "GraphicsSystem.h"
#include "Animation.h"
#include "Texture2D.h"

using namespace std;

UIElement::UIElement(std::string spriteFilepath, std::string objectKey, Direction animationDirection, float distanceToMove, float speed, Vector2D location)
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
	mSpeed = speed;

	mIsAnimating = false;
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
	mSpeed = 0.0f;

	mLoc = location;
	mAnimationDirection = (Direction)-1;

	mIsAnimating = false;
}

UIElement::~UIElement()
{

}

void UIElement::update(float deltaTime)
{
	if (mDrawingMode == GameObject2D::AnimationMode)
	{
		mpAnimation->setReversed(!mIsAnimating);

		mpAnimation->update(deltaTime);
	}
	else
	{
		if (mAnimationDirection == Direction::Left)
		{
			if (mIsAnimating && mLoc.getX() > mOrigLoc.getX() - mDistToMove)
			{
				mLoc.setX(mLoc.getX() - mDistToMove * deltaTime * mSpeed);
			}
			else if (!mIsAnimating && mLoc.getX() < mOrigLoc.getX())
			{
				mLoc.setX(mLoc.getX() + mDistToMove * deltaTime * mSpeed);
			}
		}
		else if (mAnimationDirection == Direction::Right)
		{
			if (mIsAnimating && mLoc.getX() < mOrigLoc.getX() + mDistToMove)
			{
				mLoc.setX(mLoc.getX() + mDistToMove * deltaTime * mSpeed);
			}
			else if (!mIsAnimating && mLoc.getX() > mOrigLoc.getX())
			{
				mLoc.setX(mLoc.getX() - mDistToMove * deltaTime * mSpeed);
			}
		}
		else if (mAnimationDirection == Direction::Up)
		{
			if (mIsAnimating && mLoc.getY() < mOrigLoc.getY() + mDistToMove)
			{
				mLoc.setY(mLoc.getY() + mDistToMove * deltaTime * mSpeed);
			}
			else if (!mIsAnimating && mLoc.getY() > mOrigLoc.getY())
			{
				mLoc.setY(mLoc.getY() - mDistToMove * deltaTime * mSpeed);
			}
		}
		else if (mAnimationDirection == Direction::Down)
		{
			if (mIsAnimating && mLoc.getY() > mOrigLoc.getY() - mDistToMove)
			{
				mLoc.setY(mLoc.getY() - mDistToMove * deltaTime * mSpeed);
			}
			else if (!mIsAnimating && mLoc.getY() < mOrigLoc.getY())
			{
				mLoc.setY(mLoc.getY() + mDistToMove * deltaTime * mSpeed);
			}
		}
	}
	
}
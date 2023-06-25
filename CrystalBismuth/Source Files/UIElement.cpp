#include "UIElement.h"
#include "GraphicsSystem.h"
#include "Animation.h"
#include "Texture2D.h"

using namespace std;

UIElement::UIElement(std::string spriteFilepath, std::string objectKey, Direction animationDirection, float distanceToMove, float speed, Vector2D location, Vector2D scale, GameObject2D* parent, bool animateOnHover)
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	
	Texture2D* tex = gs->createAndAddTexture2D(objectKey, spriteFilepath, true);

	mDrawingMode = GameObject2D::SpriteMode;
	mImage.s = gs->createAndAddSprite(objectKey, &tex, Vector2D::Zero(), tex->getSize(), scale);

	mLoc = location;
	mOrigLoc = location;
	mDistToMove = distanceToMove;
	mSpeed = speed;

	mIsAnimating = false;
	mAnimationDirection = animationDirection;
	mAnimateOnHover = animateOnHover;

	mParent = parent;
}

UIElement::UIElement(std::string animationTextureFilepath, std::string objectKey, int animationColumns, int animationRows, Vector2D location, bool animateOnHover)
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	
	Texture2D* tex = gs->createAndAddTexture2D(objectKey, animationTextureFilepath, true);
	gs->createAndAddAnimationData(objectKey, &tex, animationColumns, animationRows);

	mDrawingMode = GameObject2D::AnimationMode;
	mImage.a = gs->createAndAddAnimation(objectKey, objectKey, 60);
	mDistToMove = 0.0f;
	mSpeed = 0.0f;

	mLoc = location;
	mAnimationDirection = (Direction)-1;
	mAnimateOnHover = animateOnHover;

	mIsAnimating = false;
}

UIElement::~UIElement()
{

}

void UIElement::update(float deltaTime)
{
	if (mParent != nullptr)
	{
		UIElement* parent = (UIElement*)mParent;

		if (parent->getIsAnimating())
			return;
	}

	if (mDrawingMode == GameObject2D::AnimationMode)
	{
		mImage.a->setReversed(!mIsAnimating);

		mImage.a->update(deltaTime);
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
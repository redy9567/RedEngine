#include "GameObject2D.h"
#include "Animation.h"
#include "Sprite.h"

GameObject2D::GameObject2D()
{
	mLoc = Vector2D::Zero();
	mDrawingMode = DrawMode::None;
	mImage.s = nullptr;
}

GameObject2D::~GameObject2D()
{

}

GameObject2D::GameObject2D(Sprite* sprite, Vector2D location)
{
	mLoc = location;
	mDrawingMode = DrawMode::SpriteMode;
	mImage.s = sprite;
}

GameObject2D::GameObject2D(Animation* animation, Vector2D location)
{
	mLoc = location;
	mDrawingMode = DrawMode::AnimationMode;
	mImage.a = animation;
}

Vector2D GameObject2D::getSize()
{
	switch (mDrawingMode)
	{
	case DrawMode::SpriteMode:
		return mImage.s->getSize();
		break;
	case DrawMode::AnimationMode:
		return mImage.a->getCurrentSprite()->getSize();
		break;
	default:
		return Vector2D::Zero();
		break;
	}
}
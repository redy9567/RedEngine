#include "GameObject2D.h"

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
#include "GameObject2D.h"
#include "Animation.h"
#include "Sprite.h"
#include "GraphicsSystem.h"

GameObject2D::GameObject2D()
{
	mLoc = Vector2D::Zero();
	mDrawingMode = DrawMode::None;
	mImage.s = nullptr;
}

GameObject2D::~GameObject2D()
{

}

GameObject2D::GameObject2D(Sprite* sprite, Vector2D location, GameObject2D* parent)
{
	mLoc = location;
	mDrawingMode = DrawMode::SpriteMode;
	mImage.s = sprite;
	mParent = parent;
}

GameObject2D::GameObject2D(Animation* animation, Vector2D location, GameObject2D* parent)
{
	mLoc = location;
	mDrawingMode = DrawMode::AnimationMode;
	mImage.a = animation;
	mParent = parent;
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

Vector2D GameObject2D::getGameSize()
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	switch (mDrawingMode)
	{
	case DrawMode::SpriteMode:
		return gs->convertToGridCoordinates(mImage.s->getSize());
		break;
	case DrawMode::AnimationMode:
		return gs->convertToGridCoordinates(mImage.a->getCurrentSprite()->getSize());
		break;
	default:
		return Vector2D::Zero();
		break;
	}
}
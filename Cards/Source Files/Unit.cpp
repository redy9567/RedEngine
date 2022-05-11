#include "Unit.h"
#include "GraphicsSystem.h"
#include "Animation.h"
#include "Sprite.h"

Unit::Unit()
{
	mIsAnimated = false;
}

Unit::Unit(Animation* anim, Vector2D loc, Vector2D moveDir, float speed)
{
	mVisual.anim = anim;
	mLoc = loc;
	mMoveDir = moveDir.normalized();
	mSpeed = speed;
	mIsAnimated = true;
}

Unit::Unit(Sprite* sprite, Vector2D loc, Vector2D moveDir, float speed)
{
	mVisual.sprite = sprite;
	mLoc = loc;
	mMoveDir = moveDir.normalized();
	mSpeed = speed;
	mIsAnimated = false;
}

Unit::~Unit()
{

}

void Unit::draw(GraphicsSystem* gs)
{
	Sprite* currentSprite;

	if (mIsAnimated)
		currentSprite = mVisual.anim->getCurrentSprite();
	else
		currentSprite = mVisual.sprite;

	gs->draw(currentSprite, mLoc - (currentSprite->getSize() * currentSprite->getScale()) / 2.0f); //Draw the sprite at the center of the unit location
}

void Unit::update(float deltaTime)
{
	mLoc += mMoveDir * deltaTime * mSpeed;
}
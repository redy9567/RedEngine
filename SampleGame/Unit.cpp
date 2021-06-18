#include "Unit.h"
#include "GraphicsSystem.h"
#include "Animation.h"
#include "Sprite.h"

Unit::Unit()
{
	mAnimation = nullptr;
}

Unit::Unit(Animation* anim, Vector2D loc)
{
	mAnimation = anim;
	mLoc = loc;
}

Unit::~Unit()
{

}

void Unit::draw(GraphicsSystem* gs)
{
	
	gs->draw(mAnimation->getCurrentSprite(), mLoc - mAnimation->getCurrentSprite()->getSize() / 2.0f); //Draw the sprite at the center of the unit location
}
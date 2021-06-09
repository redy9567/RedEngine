#include "Unit.h"
#include "GraphicsSystem.h"
#include "Sprite.h"

Unit::Unit()
{
	mSprite = nullptr;
}

Unit::Unit(Sprite* sprite, Vector2D loc)
{
	mSprite = sprite;
	mLoc = loc;
}

Unit::~Unit()
{

}

void Unit::draw(GraphicsSystem* gs)
{
	gs->draw(mSprite, mLoc - mSprite->getSize() / 2.0f); //Draw the sprite at the center of the unit location
}
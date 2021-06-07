#include "Unit.h"

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
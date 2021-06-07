#pragma once

#include "Trackable.h"
#include "Vector2D.h"

class Sprite;

class Unit : public Trackable
{
public:
	Unit();
	Unit(Sprite* sprite, Vector2D loc = Vector2D::Zero());
	~Unit();

private:
	Sprite* mSprite;
	Vector2D mLoc;

};

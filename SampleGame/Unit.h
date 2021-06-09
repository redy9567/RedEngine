#pragma once

#include "Trackable.h"
#include "Vector2D.h"

class Sprite;
class GraphicsSystem;

class Unit : public Trackable
{
public:
	Unit();
	Unit(Sprite* sprite, Vector2D loc = Vector2D::Zero());
	~Unit();

	void draw(GraphicsSystem* gs);

	void setLocation(Vector2D loc) { mLoc = loc; }

private:
	Sprite* mSprite;
	Vector2D mLoc;

};

#pragma once

#include "Trackable.h"
#include "Vector2D.h"

class GraphicsSystem;
class Animation;

class Unit : public Trackable
{
public:
	Unit();
	Unit(Animation* anim, Vector2D loc = Vector2D::Zero());
	~Unit();

	void draw(GraphicsSystem* gs);

	void setLocation(Vector2D loc) { mLoc = loc; }

protected:
	Animation* mAnimation;
	Vector2D mLoc;

};

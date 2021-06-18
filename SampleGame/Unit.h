#pragma once

#include "Trackable.h"
#include "Vector2D.h"

class GraphicsSystem;
class Animation;

class Unit : public Trackable
{
public:
	friend class UnitManager;

	void draw(GraphicsSystem* gs);

	void setLocation(Vector2D loc) { mLoc = loc; }

protected:
	Unit();
	Unit(Animation* anim, Vector2D loc = Vector2D::Zero());
	~Unit();

	Animation* mAnimation;
	Vector2D mLoc;

};

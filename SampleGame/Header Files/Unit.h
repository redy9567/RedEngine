#pragma once

#include "Trackable.h"
#include "Vector2D.h"
#include "Animation.h"
#include "Sprite.h"

class GraphicsSystem;

class Unit : public Trackable
{
public:
	friend class UnitManager;

	void draw(GraphicsSystem* gs);

	void setLocation(Vector2D loc) { mLoc = loc; }

	void update(float deltaTime);

	Vector2D getLocation() { return mLoc; }

protected:
	union Visual
	{
		Animation* anim;
		Sprite* sprite;
	};

	Unit();
	Unit(Animation* anim, Vector2D loc = Vector2D::Zero(), Vector2D moveDir = Vector2D::Zero(), float speed = 1.0f);
	Unit(Sprite* anim, Vector2D loc = Vector2D::Zero(), Vector2D moveDir = Vector2D::Zero(), float speed = 1.0f);
	~Unit();

	Visual mVisual;
	Vector2D mLoc, mMoveDir;
	float mSpeed;
	bool mIsAnimated;

};

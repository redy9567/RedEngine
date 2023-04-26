#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class Sprite;
class Animation;

class GameObject2D : public Trackable
{
public:
	friend class GraphicsSystem;
	friend class GameObject2DManager;

	Vector2D getLoc() { return mLoc; }
	Vector2D getSize();
	Vector2D getGameSize();

	void setLoc(Vector2D location) { mLoc = location; }

protected:
	GameObject2D();
	~GameObject2D();

	GameObject2D(Sprite*, Vector2D loc = Vector2D::Zero());
	GameObject2D(Animation*, Vector2D loc = Vector2D::Zero());

	enum DrawMode
	{
		None,
		SpriteMode,
		AnimationMode
	};

	union Image
	{
		Sprite* s;
		Animation* a;
	};

	DrawMode mDrawingMode;
	Image mImage;
	Vector2D mLoc;
};
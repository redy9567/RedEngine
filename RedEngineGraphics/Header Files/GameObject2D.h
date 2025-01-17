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

	Vector2D getLoc() { return mParent ? mLoc + mParent->getLoc() :  mLoc; }
	Vector2D getLocalLoc() { return mLoc; }
	Vector2D getSize();
	Vector2D getGameSize();
	Vector2D getScale();

	float getRotation() { return mRotation; }
	bool getIsUsingTopAnchoring() { return mUseTopAnchoring; }

	void setLoc(Vector2D location) { mLoc = location; }
	void setRotation(float rot) { mRotation = rot; }

	virtual void update(float deltaTime) {}

protected:
	GameObject2D();
	virtual ~GameObject2D();

	GameObject2D(Sprite*, Vector2D loc = Vector2D::Zero(), GameObject2D* parent = nullptr, bool useTopAnchoring = false);
	GameObject2D(Animation*, Vector2D loc = Vector2D::Zero(), GameObject2D* parent = nullptr, bool useTopAnchoring = false);

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
	float mRotation = 0.0f;

	GameObject2D* mParent;

	bool mUseTopAnchoring;
};
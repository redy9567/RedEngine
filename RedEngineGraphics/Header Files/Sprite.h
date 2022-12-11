#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class Mesh2D;
class Texture2D;

class Sprite : public Trackable
{
public:
	friend class GraphicsSystem;

	Sprite(Texture2D** texture, Vector2D textureStartLoc, Vector2D loc, Vector2D size, float scale = 1.0f);
	~Sprite();

	Vector2D getSize() { return mSize; }
	Vector2D getLocation() { return mLoc; }
	float getScale() { return mScale; }
	
private:
	Sprite() = delete;

	Mesh2D* mpMesh;
	Vector2D mLoc, mSize;
	float mScale;
};

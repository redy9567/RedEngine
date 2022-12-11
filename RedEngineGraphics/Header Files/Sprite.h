#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class Mesh2D;
class Texture2D;

class Sprite : public Trackable
{
public:
	friend class GraphicsSystem;

	Sprite(Texture2D** texture, Vector2D textureStartLoc, Vector2D loc, Vector2D size, Vector2D scale = Vector2D::One());
	~Sprite();

	Vector2D getSize() { return mSize; }
	Vector2D getLocation() { return mLoc; }
	Vector2D getScale() { return mScale; }
	
private:
	Sprite() = delete;

	Mesh2D* mpMesh;
	Vector2D mLoc, mSize;
	Vector2D mScale;
};

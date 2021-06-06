#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class GraphicsBuffer;

class Sprite : public Trackable
{
public:
	friend class GraphicsSystem;

	Sprite(GraphicsBuffer* gb, Vector2D loc, Vector2D size);
	~Sprite();

	Vector2D getSize() { return mSize; }
	Vector2D getLoc() { return mLoc; }
	
private:
	Sprite() = delete;

	GraphicsBuffer* mpGraphicsBuffer;
	Vector2D mLoc, mSize;
};

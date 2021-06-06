#include "Sprite.h"
#include "GraphicsBuffer.h"

Sprite::Sprite(GraphicsBuffer* gb, Vector2D loc, Vector2D size)
{
	mpGraphicsBuffer = gb;
	mLoc = loc;
	mSize = size;
}

Sprite::~Sprite()
{
	mpGraphicsBuffer = nullptr;
}
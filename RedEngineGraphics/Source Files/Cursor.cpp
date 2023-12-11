#include "Cursor.h"

using namespace std;

Cursor::Cursor()
{

}

Cursor::~Cursor()
{

}

void Cursor::update(Vector2D mousePos)
{
	mLoc = mousePos;
}

void Cursor::setImage(Sprite* sprite)
{
	mImage.s = sprite;

	if (sprite)
	{
		mDrawingMode = DrawMode::SpriteMode;
	}
	else
	{
		mDrawingMode = DrawMode::None;
	}
}
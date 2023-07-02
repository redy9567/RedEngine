#pragma once
#include "Cursor.h"
#include "Chicken.h"

class GameCursor : public Cursor
{
public:
	GameCursor(ChickenColor syringeColor);
	~GameCursor();

	void setSyringeColor(ChickenColor syringeColor) { mSyringeColor = syringeColor; }
	ChickenColor getSyringeColor() { return mSyringeColor; }

private:
	GameCursor() = delete;

	ChickenColor mSyringeColor;

};
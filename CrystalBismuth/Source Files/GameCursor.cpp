#include "GameCursor.h"

GameCursor::GameCursor(ChickenColor syringeColor)
{
	mData.c = syringeColor;
	mCursorType = CursorType::Syringe;
}

GameCursor::GameCursor(Building::BuildingType buildingType)
{
	mData.b = buildingType;
	mCursorType = CursorType::Building;
}

GameCursor::GameCursor()
{
	mCursorType = CursorType::Evolution;
}

GameCursor::~GameCursor()
{

}
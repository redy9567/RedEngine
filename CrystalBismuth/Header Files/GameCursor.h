#pragma once
#include "Cursor.h"
#include "Chicken.h"
#include "Building.h"

class GameCursor : public Cursor
{
public:
	enum class CursorType
	{
		Syringe,
		Building
	};

	union CursorData
	{
		ChickenColor c;
		Building::BuildingType b;
	};

	GameCursor(ChickenColor syringeColor);
	GameCursor(Building::BuildingType);
	~GameCursor();

	void setSyringeColor(ChickenColor syringeColor) { if(mCursorType == CursorType::Syringe) mData.c = syringeColor; }
	ChickenColor getSyringeColor() { return mData.c; }

	void setBuildingType(Building::BuildingType buildingType) { if (mCursorType == CursorType::Building) mData.b = buildingType; }
	Building::BuildingType getBuildingType() { return mData.b; }

	CursorType getCursorType() { return mCursorType; }

private:
	GameCursor() = delete;

	CursorData mData;
	CursorType mCursorType;

};
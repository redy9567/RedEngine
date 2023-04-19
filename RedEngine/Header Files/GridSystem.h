#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class GridSystem : public Trackable
{
public:
	static GridSystem* getInstance();
	static void cleanupInstance();

	void init(float gridBoxWidth, float gridBoxHeight);
	void cleanup();

	Vector2D convertPixelsToGrid(Vector2D pxLoc);
	Vector2D convertGridToPixels(Vector2D gridLoc);

	float getGridBoxWidth() { return mGridBoxWidth; }
	float getGridBoxHeight() { return mGridBoxHeight; }

private:
	GridSystem();
	~GridSystem();

	bool mInit;

	float mGridBoxWidth, mGridBoxHeight;

	static GridSystem* mspInstance;
};
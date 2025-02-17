#pragma once
#include "Trackable.h"
#include "Vector2D.h"

const float STARTING_GRID_COUNT_X = 43;
const float STARTING_GRID_COUNT_Y = 22;

class GridSystem : public Trackable
{
public:
	static GridSystem* getInstance();
	static void cleanupInstance();

	void init(int displayWidth, int displayHeight);
	void cleanup();

	Vector2D convertPixelsToGrid(Vector2D pxLoc);
	Vector2D convertGridToPixels(Vector2D gridLoc);

	Vector2D convertScreenToGrid(Vector2D screenLoc);

	//DEBUG: Changed to 1 to disable grid system
	float getGridBoxWidth() { return 1; }
	float getGridBoxHeight() { return 1; }

	void updateResolution(int displayWidth, int displayHeight);

private:
	GridSystem();
	~GridSystem();

	bool mInit;

	float mGridBoxWidth, mGridBoxHeight;

	static GridSystem* mspInstance;
};
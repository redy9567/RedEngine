#pragma once
#include "Trackable.h"

namespace raylib
{
	class Window;
}


class GraphicsSystem : public Trackable
{
public:
	GraphicsSystem();
	~GraphicsSystem();

	void init();
	void init(int screenWidth, int screenHeight);
	void init(int screenWidth, int screenHeight, std::string windowName);

	void cleanup();

	bool shouldExit();

	void flipGraphicsBuffer();

	void clearBackground(); //To be implemented to clear to any specific color

	void drawText(std::string text, int xLoc, int yLoc); //Implement variations

	int getScreenWidth() { return mScreenWidth; }
	int getScreenHeight() { return mScreenHeight; }

private:
	int mScreenWidth,
		mScreenHeight;

	raylib::Window* mpWindow;
};

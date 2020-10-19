#pragma once

class GraphicsSystem
{

public:
	GraphicsSystem() = delete;
	GraphicsSystem(int width, int height);
	~GraphicsSystem();

	void startLoop();

private:
	int mWidth
	,mHeight;

};

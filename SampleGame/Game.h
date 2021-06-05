#pragma once
#include "Trackable.h"

class GraphicsSystem;

class Game : public Trackable
{
public:
	static Game* getInstance();
	static void cleanupInstance();

	void init(int screenWidth, int screenHeight);
	void cleanup();

	void startGame();

private:
	Game();
	~Game();

	void getInput();
	void update();
	void render();

	static Game* mspInstance;

	GraphicsSystem* mpGraphicsSystem;
};

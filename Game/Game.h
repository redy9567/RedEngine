#pragma once
#include "GraphicsSystem.h"

class Game
{

public:
	Game();
	~Game();

	void init();
	void cleanup();

	void doLoop();

private:
	GraphicsSystem* mpGraphicsSystem;

};
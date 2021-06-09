#pragma once
#include "Trackable.h"
#include <string>

class GraphicsSystem;
class GraphicsBuffer;
class Sprite;
class InputSystem;
class Unit;

const std::string ASSET_PATH = "E:\\RedEngine\\SampleGame\\Assets\\";
const std::string SMURF_FILENAME = "smurf_sprites.png";

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
	InputSystem* mpInputSystem;

	GraphicsBuffer* mpSmurfBuffer;
	Sprite* mpSmurfSprite;
	Unit* mpSmurfUnit;
	
};

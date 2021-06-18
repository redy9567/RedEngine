#pragma once
#include "Trackable.h"
#include <string>

class GraphicsSystem;
class GraphicsBuffer;
class Animation;
class InputSystem;
class Player;
class Timer;
class UnitManager;

const std::string ASSET_PATH = "../SampleGame/Assets/";
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

	void createRandomUnit();

	static Game* mspInstance;

	GraphicsSystem* mpGraphicsSystem;
	InputSystem* mpInputSystem;

	UnitManager* mpUnitManager;

	GraphicsBuffer* mpSmurfBuffer;
	Animation* mpSmurfAnimation;
	Player* mpPlayerUnit;

	Timer* mpGameTimer;

	double deltaTime;
	
};

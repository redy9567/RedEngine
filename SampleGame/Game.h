#pragma once
#include "Trackable.h"
#include <string>

class GraphicsSystem;
class GraphicsBuffer;
class AnimationData; //To Be Removed
class InputSystem;
class Player;
class Timer;
class UnitManager;
class AnimationManager;

const std::string ASSET_PATH = "../SampleGame/Assets/";
const std::string SMURF_FILENAME = "smurf_sprites.png";
const std::string PROJECTILE_FILENAME = "Sphere_Glow.png";

const float PROJECTILE_SPEED = 100.0f;

class Game : public Trackable
{
public:
	static Game* getInstance();
	static void cleanupInstance();

	void init(int screenWidth, int screenHeight, int fps = 60, bool debugMode = false);
	void cleanup();

	void startGame();

private:
	Game();
	~Game();

	void getInput();
	void update();
	void render();

	void debug(); //Just a bunch of stuff to do in Debug Mode

	static Game* mspInstance;

	GraphicsSystem* mpGraphicsSystem;
	InputSystem* mpInputSystem;

	UnitManager* mpUnitManager;
	AnimationManager* mpAnimationManager;

	GraphicsBuffer* mpSmurfBuffer;
	GraphicsBuffer* mpProjBuffer;
	AnimationData* mpSmurfAnimationData; //TBD
	AnimationData* mpProjAnimationData; //TBD
	Player* mpPlayerUnit;

	Timer* mpGameTimer;

	double deltaTime;
	bool mDebugMode, mIsPlaying;

	float mTimePerFrame;
	
};

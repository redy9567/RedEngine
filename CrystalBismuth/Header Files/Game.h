#pragma once
#include "Trackable.h"

class GraphicsSystem;
class Sprite;
class Texture2D;
class ShaderManager;
class AnimationData;
class Animation;
class Timer;
class InputSystem;
//class Chicken;

class Game : public Trackable
{

public:
	static Game* getInstance();
	static void cleanupInstance();

	void init(int mFPS);
	void cleanup();
	void play();

	int debugGetFPS() { return mDebugMode ? 1 / mDeltaTime : -1; }

private:
	Game();
	~Game();

	bool gameLoop();

	void input();
	void update();
	bool render();

	void initShaderObjects();
	void initShaderPrograms();

	static Game* mspInstance;


	GraphicsSystem* mpGraphicsSystem;
	InputSystem* mpInputSystem;

	//Timing Stuff
	float mTimePerFrame;
	Timer* mpTimer;
	float mDeltaTime;

	//Are we in Debug Mode?
	bool mDebugMode;

	//Keyboard stuff
	bool mInputLastF1State;
	bool mInputLastF2State;
	bool mInputLastF4State;
	bool mInputLastF5State;

	//Game Data
	Texture2D* mpChickWalkingTexture;
	Texture2D** mpTextureCollection;

	//Chicken* mpChicken;

};

#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class GraphicsSystem;
class Sprite;
class Texture2D;
class ShaderManager;
class AnimationData;
class Animation;
class Timer;
class InputSystem;
class Chicken;
class UIButton;

const float MONEY_TEXT_VERTICAL_OFFSET = 20.0f;
const float MONEY_TEXT_HORIZONTAL_OFFSET = 60.0f;
const int EGG_SELL_AMOUNT = 5;

const int GAME_DISPLAY_WIDTH = 1920;
const int GAME_DISPLAY_HEIGHT = 1080;

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

	bool isPointWithinBounds(Vector2D point, Vector2D lower, Vector2D upper);

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

	Chicken* mpChicken;
	UIButton* mpButton;
	UIButton* mpButton2;

	int mCurrentMoney;

};

#pragma once
#include "Trackable.h"
#include "Vector2D.h"
#include "MouseEvent.h"

class GraphicsSystem;
class Sprite;
class Texture2D;
class ShaderManager;
class AnimationData;
class Animation;
class Timer;
class InputSystem;
class Chicken;
class UIElement;
class ChickenManager;
class Mesh2D;
class GameObject2D;
class GameListener;

const float CURRENCY_UI_MOVE_DISTANCE = 47.0f;
const float CURRENCY_UI_ANIMATION_SPEED = 5.0f;
const float MONEY_TEXT_VERTICAL_OFFSET = 20.0f;
const float MONEY_TEXT_HORIZONTAL_OFFSET = 60.0f;
const float CURRENCY_UI_VERTICAL_OFFSET = 20.0f;
const float CURRENCY_UI_HORIZONTAL_OFFSET = 18.0f;

const float SCIENCE_UI_MOVE_DISTANCE = 47.0f;
const float SCIENCE_UI_ANIMATION_SPEED = 5.0f;
const float SCIENCE_UI_VERTICAL_OFFSET = 55.0f;
const float SCIENCE_UI_HORIZONTAL_OFFSET = 18.0f;

const int EGG_SELL_AMOUNT = 5;

const int GAME_DISPLAY_WIDTH = 1536;
const int GAME_DISPLAY_HEIGHT = 864;

class Game : public Trackable
{

public:
	friend class GameListener;

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

	//Event Functions
	void checkChickenClicked(Vector2D mousePos, MouseAction mouseButton);

	void onChickenLeftClick(Chicken* ckn);
	void onChickenRightClick(Chicken* ckn);

	void onMouseMove(Vector2D mousePos);

	void onToggleDrawMode();
	void onToggleShaders();
	void onShaderHotReload();
	void onToggleDebugMode();

	void startMouseDrag(Vector2D mousePos);
	void stopMouseDrag();

	void moveDebugChicken(Vector2D mousePos);

	static Game* mspInstance;


	GraphicsSystem* mpGraphicsSystem;
	InputSystem* mpInputSystem;
	ChickenManager* mpChickenManager;

	Chicken* mpSelectedChicken;
	Mesh2D* mpChickenSelectionMesh;

	GameObject2D* mpBackground;

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

	UIElement* mpButton;
	UIElement* mpButton2;
	
	UIElement* mpCurrencyUI;
	UIElement* mpScienceUI;

	int mCurrentMoney;

	GameListener* mpGameListener;

};

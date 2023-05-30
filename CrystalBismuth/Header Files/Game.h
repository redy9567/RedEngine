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

const int GAME_DISPLAY_WIDTH = 1536;
const int GAME_DISPLAY_HEIGHT = 864;

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

const float BASE_BUTTON_UI_MOVE_DISTANCE = 45.0f;
const float BASE_BUTTON_UI_ANIMATION_SPEED = 8.0f;
const float SHOP_BUTTON_UI_X = -150.0f;
const float BASE_BUTTON_UI_Y = 295.0f;

const float COOP_BUTTON_UI_X = 0.0f;
const float PEN_BUTTON_UI_X = 150.0f;
const float HATCHERY_BUTTON_UI_X = -150.0f;
const float SCIENCE_BUTTON_UI_X = 0.0f;
const float SETTINGS_BUTTON_UI_X = 150.0f;

const float BUTTON_SCALE = 1.5f;

const float BASE_WINDOW_UI_MOVE_DISTANCE = 493.75f;
const float BASE_WINDOW_UI_ANIMATION_SPEED = 3.0f;
const float FIRST_WINDOW_UI_X = 260.0f;
const float FIRST_WINDOW_UI_Y = -250.0f;
const float SECOND_WINDOW_UI_X = GAME_DISPLAY_WIDTH - 260.0f;
const float SECOND_WINDOW_UI_Y = FIRST_WINDOW_UI_Y;

const float WINDOW_SCALE = 4.0f;

const int EGG_SELL_AMOUNT = 5;

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
	void checkUIClicked(const MouseEvent event);

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

	UIElement* mpShopButtonUI;
	UIElement* mpShopUI;

	UIElement* mpCoopButtonUI;
	UIElement* mpCoopUI;

	UIElement* mpPenButtonUI;
	UIElement* mpPenUI;

	UIElement* mpHatcheryButtonUI;
	UIElement* mpHatcheryUI;

	UIElement* mpScienceButtonUI;
	UIElement* mpScienceWindowUI;

	UIElement* mpSettingsButtonUI;
	UIElement* mpSettingsUI;
	
	UIElement* mpCurrencyUI;
	UIElement* mpScienceUI;

	int mCurrentMoney;

	GameListener* mpGameListener;

};

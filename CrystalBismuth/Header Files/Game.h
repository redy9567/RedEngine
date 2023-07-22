#pragma once
#include "Trackable.h"
#include "Vector2D.h"
#include "MouseEvent.h"
#include "Chicken.h"

class GraphicsSystem;
class Sprite;
class Texture2D;
class ShaderManager;
class AnimationData;
class Animation;
class Timer;
class InputSystem;
class UIManager;
class ChickenManager;
class Mesh2D;
class GameObject2D;
class GameListener;
class GameCursor;

const int GAME_DISPLAY_WIDTH = 1536;
const int GAME_DISPLAY_HEIGHT = 864;

const std::string PURPLE_SYRINGE_KEY = "purpleSyringe";
const std::string BLACK_SYRINGE_KEY = "blackSyringe";
const std::string BLUE_SYRINGE_KEY = "blueSyringe";
const std::string LIGHT_BLUE_SYRINGE_KEY = "lightBlueSyringe";
const std::string GREEN_SYRINGE_KEY = "greenSyringe";
const std::string YELLOW_SYRINGE_KEY = "yellowSyringe";
const std::string RED_SYRINGE_KEY = "redSyringe";

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
const float TREE_BUTTON_SCALE = 4.0f;
const float SUB_TREE_BUTTON_SCALE = 5.0f;

const float BASE_WINDOW_UI_MOVE_DISTANCE = 493.75f;
const float BASE_WINDOW_UI_ANIMATION_SPEED = 3.0f;
const float FIRST_WINDOW_UI_X = 260.0f;
const float FIRST_WINDOW_UI_Y = -250.0f;
const float SECOND_WINDOW_UI_X = GAME_DISPLAY_WIDTH - 260.0f;
const float SECOND_WINDOW_UI_Y = FIRST_WINDOW_UI_Y;

const float RESEARCH_TREE_OFFSET_Y = 250.0f;
const float RESEARCH_TREE_OFFSET_X = -280.0f;
const float SCIENCE_TREE_OFFSET_Y = 220.0f;
const float SCIENCE_TREE_OFFSET_X = -260.0f;

const float TREE_UI_BUTTON_OFFSET_1_X = -275.0f;
const float TREE_UI_BUTTON_OFFSET_1_Y = 425.0f;

const float TREE_UI_BUTTON_OFFSET_2_X = -350.0f;
const float TREE_UI_BUTTON_OFFSET_2_Y = 320.0f;
const float TREE_UI_BUTTON_OFFSET_3_X = -195.0f;
const float TREE_UI_BUTTON_OFFSET_3_Y = 320.0f;

const float TREE_UI_BUTTON_OFFSET_4_X = -425.0f;
const float TREE_UI_BUTTON_OFFSET_4_Y = 235.0f;
const float TREE_UI_BUTTON_OFFSET_5_X = -275.0f;
const float TREE_UI_BUTTON_OFFSET_5_Y = 232.5f;
const float TREE_UI_BUTTON_OFFSET_6_X = -120.0f;
const float TREE_UI_BUTTON_OFFSET_6_Y = 235.0f;

const float TREE_UI_BUTTON_OFFSET_7_X = -350.0f;
const float TREE_UI_BUTTON_OFFSET_7_Y = 145.0f;
const float TREE_UI_BUTTON_OFFSET_8_X = -195.0f;
const float TREE_UI_BUTTON_OFFSET_8_Y = 145.0f;

const float TREE_UI_BUTTON_OFFSET_9_X = -275.0f;
const float TREE_UI_BUTTON_OFFSET_9_Y = 70.0f;

const float SCIENCE_UI_BUTTON_OFFSET_1_X = -265.0f;
const float SCIENCE_UI_BUTTON_OFFSET_1_Y = 350.0f;

const float SCIENCE_UI_BUTTON_OFFSET_2_X = -265.0f;
const float SCIENCE_UI_BUTTON_OFFSET_2_Y = 220.0f;
const float SCIENCE_UI_BUTTON_OFFSET_3_X = -365.0f;
const float SCIENCE_UI_BUTTON_OFFSET_3_Y = 220.0f;
const float SCIENCE_UI_BUTTON_OFFSET_4_X = -165.0f;
const float SCIENCE_UI_BUTTON_OFFSET_4_Y = 220.0f;

const float SCIENCE_UI_BUTTON_OFFSET_5_X = -365.0f;
const float SCIENCE_UI_BUTTON_OFFSET_5_Y = 147.5f;
const float SCIENCE_UI_BUTTON_OFFSET_6_X = -165.0f;
const float SCIENCE_UI_BUTTON_OFFSET_6_Y = 147.5f;

const float SCIENCE_UI_BUTTON_OFFSET_7_X = -265.0f;
const float SCIENCE_UI_BUTTON_OFFSET_7_Y = 65.0f;

const float WINDOW_SCALE = 4.0f;
const float BASE_TREE_SCALE = 5.0f;
const float SCIENCE_TREE_SCALE = 4.5f;
const float SCIENCE_BUTTON_SCALE = 3.0f;

const float SCROLL_WINDOW_SPEED = 10.0f;
const Vector2D SCROLL_WINDOW_INSET(15, 15);

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

	void setMouseToSyringe(ChickenColor color, Vector2D mousePos);

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
	void onClick(const MouseEvent event);
	bool checkUIClicked(const MouseEvent event);

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
	UIManager* mpUIManager;

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

	int mCurrentMoney;

	GameListener* mpGameListener;

	GameCursor* mpGameCursor;

};

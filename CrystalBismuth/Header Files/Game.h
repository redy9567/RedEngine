#pragma once
#include "Trackable.h"
#include "Vector2D.h"
#include "MouseEvent.h"
#include "Chicken.h"
#include "Building.h"

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
class UIElement;

const int GAME_DISPLAY_WIDTH = 1536;
const int GAME_DISPLAY_HEIGHT = 864;

const std::string PURPLE_SYRINGE_KEY = "purpleSyringe";
const std::string BLACK_SYRINGE_KEY = "blackSyringe";
const std::string BLUE_SYRINGE_KEY = "blueSyringe";
const std::string LIGHT_BLUE_SYRINGE_KEY = "lightBlueSyringe";
const std::string GREEN_SYRINGE_KEY = "greenSyringe";
const std::string YELLOW_SYRINGE_KEY = "yellowSyringe";
const std::string RED_SYRINGE_KEY = "redSyringe";

const float CURRENCY_UI_MOVE_DISTANCE = 0.0306f;
const float CURRENCY_UI_ANIMATION_SPEED = 5.0f; 
const float MONEY_TEXT_VERTICAL_LOC = 0.977f;
const float MONEY_TEXT_HORIZONTAL_LOC = 0.961f;
const float CURRENCY_UI_VERTICAL_OFFSET = 0.0231f;
const float CURRENCY_UI_HORIZONTAL_OFFSET = 0.0117f;

const float SCIENCE_TEXT_VERTICAL_LOC = 0.931f;
const float SCIENCE_TEXT_HORIZONTAL_LOC = 0.961f;

const float SCIENCE_UI_MOVE_DISTANCE = 0.0306f;
const float SCIENCE_UI_ANIMATION_SPEED = 5.0f; 
const float SCIENCE_UI_VERTICAL_OFFSET = 0.0637f;
const float SCIENCE_UI_HORIZONTAL_OFFSET = 0.0117f;

const float BASE_BUTTON_UI_MOVE_DISTANCE = 0.0521f;
const float BASE_BUTTON_UI_ANIMATION_SPEED = 8.0f; 
const float SHOP_BUTTON_UI_X = -0.0977f;
const float BASE_BUTTON_UI_Y = 0.34144f;

const float COOP_BUTTON_UI_X = 0.0f;
const float PEN_BUTTON_UI_X = 0.0977f;
const float HATCHERY_BUTTON_UI_X = -0.0977f;
const float SCIENCE_BUTTON_UI_X = 0.0f;
const float SETTINGS_BUTTON_UI_X = 0.0977f;

const float BUTTON_SCALE = 1.5f;
const float TREE_BUTTON_SCALE = 4.0f;
const float SUB_TREE_BUTTON_SCALE = 5.0f;

const float BASE_WINDOW_UI_MOVE_DISTANCE = 0.5715f;
const float BASE_WINDOW_UI_ANIMATION_SPEED = 3.0f; 
const float FIRST_WINDOW_UI_X = 0.16927f;
const float FIRST_WINDOW_UI_Y = -0.28935f;
const float SECOND_WINDOW_UI_X = 0.8307f;
const float SECOND_WINDOW_UI_Y = FIRST_WINDOW_UI_Y;

const float RESEARCH_TREE_OFFSET_Y = 0.2894f;
const float RESEARCH_TREE_OFFSET_X = -0.1823f;
const float SCIENCE_TREE_OFFSET_Y = 0.2546f;
const float SCIENCE_TREE_OFFSET_X = -0.1693f;

const float TREE_UI_BUTTON_OFFSET_1_X = -0.1790f;
const float TREE_UI_BUTTON_OFFSET_1_Y = 0.4919f;

const float TREE_UI_BUTTON_OFFSET_2_X = -0.2279f;
const float TREE_UI_BUTTON_OFFSET_2_Y = 0.3704f;
const float TREE_UI_BUTTON_OFFSET_3_X = -0.1270f;
const float TREE_UI_BUTTON_OFFSET_3_Y = 0.3704f;

const float TREE_UI_BUTTON_OFFSET_4_X = -0.2767f;
const float TREE_UI_BUTTON_OFFSET_4_Y = 0.2720f;
const float TREE_UI_BUTTON_OFFSET_5_X = -0.1790f;
const float TREE_UI_BUTTON_OFFSET_5_Y = 0.2691f;
const float TREE_UI_BUTTON_OFFSET_6_X = -0.0781f;
const float TREE_UI_BUTTON_OFFSET_6_Y = 0.2720f;

const float TREE_UI_BUTTON_OFFSET_7_X = -0.2279f;
const float TREE_UI_BUTTON_OFFSET_7_Y = 0.1678f;
const float TREE_UI_BUTTON_OFFSET_8_X = -0.1270f;
const float TREE_UI_BUTTON_OFFSET_8_Y = 0.1678f;

const float TREE_UI_BUTTON_OFFSET_9_X = -0.1790f;
const float TREE_UI_BUTTON_OFFSET_9_Y = 0.0810f;

const float SCIENCE_UI_BUTTON_OFFSET_1_X = -0.1725f;
const float SCIENCE_UI_BUTTON_OFFSET_1_Y = 0.4051f;

const float SCIENCE_UI_BUTTON_OFFSET_2_X = -0.1725f;
const float SCIENCE_UI_BUTTON_OFFSET_2_Y = 0.2546f;
const float SCIENCE_UI_BUTTON_OFFSET_3_X = -0.2376f;
const float SCIENCE_UI_BUTTON_OFFSET_3_Y = 0.2546f;
const float SCIENCE_UI_BUTTON_OFFSET_4_X = -0.1074f;
const float SCIENCE_UI_BUTTON_OFFSET_4_Y = 0.2546f;

const float SCIENCE_UI_BUTTON_OFFSET_5_X = -0.2376f;
const float SCIENCE_UI_BUTTON_OFFSET_5_Y = 0.1707f;
const float SCIENCE_UI_BUTTON_OFFSET_6_X = -0.1074f;
const float SCIENCE_UI_BUTTON_OFFSET_6_Y = 0.1707f;

const float SCIENCE_UI_BUTTON_OFFSET_7_X = -0.1725f;
const float SCIENCE_UI_BUTTON_OFFSET_7_Y = 0.0752f;

const float WINDOW_SCALE = 4.0f;
const float BASE_TREE_SCALE = 5.0f;
const float SCIENCE_TREE_SCALE = 4.5f;
const float SCIENCE_BUTTON_SCALE = 3.0f;

const float SCROLL_WINDOW_SPEED = 0.1f;
const Vector2D SCROLL_WINDOW_INSET(0.0098f, 0.0174f);

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

	bool buySyringe(ChickenColor, Vector2D mousePos, int cost);
	bool buyBuilding(Building::BuildingType, Vector2D mousePos, int cost);
	bool buyEvolution(Vector2D mousePos, int cost);

private:
	Game();
	~Game();

	void loadData();

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

	void setMouseToSyringe(ChickenColor color, Vector2D mousePos);
	void setMouseToBuilding(Building::BuildingType buildingType, Vector2D mousePos);
	void setMouseToEvolution(Vector2D mousePos);

	void placeBuilding(Building::BuildingType buildingType, Vector2D pos);

	void addResearch(int amount) { mCurrentScience += amount; }

	static Game* mspInstance;


	GraphicsSystem* mpGraphicsSystem;
	InputSystem* mpInputSystem;
	ChickenManager* mpChickenManager;
	UIManager* mpUIManager;

	Chicken* mpSelectedChicken;
	Mesh2D* mpChickenSelectionMesh;

	GameObject2D* mpBackground;

	UIElement* mpBuildingHighlight;

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
	int mCurrentScience;

	GameListener* mpGameListener;

	GameCursor* mpGameCursor;

};

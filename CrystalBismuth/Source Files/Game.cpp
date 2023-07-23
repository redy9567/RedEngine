#include "Game.h"
#include "Mesh2D.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Texture2D.h"
#include "ShaderManager.h"
#include "Animation.h"
#include "AnimationData.h"
#include "Timer.h"
#include "InputSystem.h"
#include "DebugHUD.h"
#include "Chicken.h";
#include "UIElement.h"
#include "ChickenManager.h"
#include "Camera2D.h"
#include "Vector4D.h"
#include "EventSystem.h"
#include "GameEvents.h"
#include "GameListener.h"
#include "GridSystem.h"
#include "UIManager.h"
#include "GameCursor.h"
#include "SyringeButton.h"
#include <fstream>

#include <assert.h>
#include <iostream>

using namespace std;

Game* Game::mspInstance = nullptr;

Game* Game::getInstance()
{
	if (!mspInstance)
		mspInstance = new Game();

	return mspInstance;
}

void Game::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

Game::Game()
{
	mpGraphicsSystem = nullptr;

	mInputLastF1State = false;
	mInputLastF2State = false;
	mInputLastF4State = false;
	mInputLastF5State = false;

	mDebugMode = false;

	mpSelectedChicken = nullptr;

	mpGameListener = nullptr;
}

Game::~Game()
{

}

void Game::init(int mFPS)
{

	mpGraphicsSystem = GraphicsSystem::getInstance();
	mpInputSystem = InputSystem::getInstance();

	assert(mpGraphicsSystem->init(GAME_DISPLAY_WIDTH, GAME_DISPLAY_HEIGHT));

	initShaderObjects();

	initShaderPrograms();

	Texture2D* bgTexture = mpGraphicsSystem->createAndAddTexture2D("Background", RESOURCES_DIRECTORY + BACKGROUNDS_DIRECTORY + BACKGROUND_FILENAME, true);
	Vector2D bgScale = Vector2D(2, 2);
	Sprite* bgSprite = mpGraphicsSystem->createAndAddSprite("Background", &bgTexture, Vector2D::Zero(), bgTexture->getSize(), bgScale);
	mpBackground = mpGraphicsSystem->createAndAddGameObject2D(bgSprite, Vector2D(21.5f, 19.5f));
	mpGraphicsSystem->setBackground(mpBackground);

	mpChickenManager = ChickenManager::getInstance();
	mpChickenManager->createAndAddChicken(ChickenColor::WHITE, Vector2D(9, 5));
	mpChickenManager->createAndAddChicken(ChickenColor::WHITE, Vector2D(10, 5));

	mpUIManager = UIManager::getInstance();
	mpUIManager->init();

	Vector2D purpleSyringeButtonLoc = Vector2D(-200, 200);
	Vector2D blackSyringeButtonLoc = Vector2D(-200, 150);
	Vector2D blueSyringeButtonLoc = Vector2D(-200, 100);
	Vector2D lightBlueSyringeButtonLoc = Vector2D(-200, 50);
	Vector2D greenSyringeButtonLoc = Vector2D(-200, 0);
	Vector2D yellowSyringeButtonLoc = Vector2D(-200, -50);
	Vector2D redSyringeButtonLoc = Vector2D(-200, -100);

	Texture2D* purpleSyringeTexture = mpGraphicsSystem->createAndAddTexture2D(PURPLE_SYRINGE_KEY, PURPLE_SYRINGE_FILEPATH, true);
	Sprite* purpleSyringeSprite = mpGraphicsSystem->createAndAddSprite(PURPLE_SYRINGE_KEY, &purpleSyringeTexture, Vector2D::Zero(), purpleSyringeTexture->getSize(), Vector2D::One(), ImageAnchor::BottomLeft);
	Texture2D* blackSyringeTexture = mpGraphicsSystem->createAndAddTexture2D(BLACK_SYRINGE_KEY, BLACK_SYRINGE_FILEPATH, true);
	Sprite* blackSyringeSprite = mpGraphicsSystem->createAndAddSprite(BLACK_SYRINGE_KEY, &blackSyringeTexture, Vector2D::Zero(), blackSyringeTexture->getSize(), Vector2D::One(), ImageAnchor::BottomLeft);
	Texture2D* blueSyringeTexture = mpGraphicsSystem->createAndAddTexture2D(BLUE_SYRINGE_KEY, BLUE_SYRINGE_FILEPATH, true);
	Sprite* blueSyringeSprite = mpGraphicsSystem->createAndAddSprite(BLUE_SYRINGE_KEY, &blueSyringeTexture, Vector2D::Zero(), blueSyringeTexture->getSize(), Vector2D::One(), ImageAnchor::BottomLeft);
	Texture2D* lightBlueSyringeTexture = mpGraphicsSystem->createAndAddTexture2D(LIGHT_BLUE_SYRINGE_KEY, LIGHT_BLUE_SYRINGE_FILEPATH, true);
	Sprite* lightBlueSyringeSprite = mpGraphicsSystem->createAndAddSprite(LIGHT_BLUE_SYRINGE_KEY, &lightBlueSyringeTexture, Vector2D::Zero(), lightBlueSyringeTexture->getSize(), Vector2D::One(), ImageAnchor::BottomLeft);
	Texture2D* greenSyringeTexture = mpGraphicsSystem->createAndAddTexture2D(GREEN_SYRINGE_KEY, GREEN_SYRINGE_FILEPATH, true);
	Sprite* greenSyringeSprite = mpGraphicsSystem->createAndAddSprite(GREEN_SYRINGE_KEY, &greenSyringeTexture, Vector2D::Zero(), greenSyringeTexture->getSize(), Vector2D::One(), ImageAnchor::BottomLeft);
	Texture2D* yellowSyringeTexture = mpGraphicsSystem->createAndAddTexture2D(YELLOW_SYRINGE_KEY, YELLOW_SYRINGE_FILEPATH, true);
	Sprite* yellowSyringeSprite = mpGraphicsSystem->createAndAddSprite(YELLOW_SYRINGE_KEY, &yellowSyringeTexture, Vector2D::Zero(), yellowSyringeTexture->getSize(), Vector2D::One(), ImageAnchor::BottomLeft);
	Texture2D* redSyringeTexture = mpGraphicsSystem->createAndAddTexture2D(RED_SYRINGE_KEY, RED_SYRINGE_FILEPATH, true);
	Sprite* redSyringeSprite = mpGraphicsSystem->createAndAddSprite(RED_SYRINGE_KEY, &redSyringeTexture, Vector2D::Zero(), redSyringeTexture->getSize(), Vector2D::One(), ImageAnchor::BottomLeft);

	Vector2D shopButtonUILoc = Vector2D(SHOP_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D firstWindowUILoc = Vector2D(FIRST_WINDOW_UI_X, FIRST_WINDOW_UI_Y);
	Vector2D secondWindowUILoc = Vector2D(SECOND_WINDOW_UI_X, SECOND_WINDOW_UI_Y);

	Vector2D coopButtonUILoc = Vector2D(COOP_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D penButtonUILoc = Vector2D(PEN_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D hatcheryButtonUILoc = Vector2D(HATCHERY_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D scienceButtonUILoc = Vector2D(SCIENCE_BUTTON_UI_X, BASE_BUTTON_UI_Y);
	Vector2D settingsButtonUILoc = Vector2D(SETTINGS_BUTTON_UI_X, BASE_BUTTON_UI_Y);

	Vector2D reserachTreeUIOffset = Vector2D(RESEARCH_TREE_OFFSET_X, RESEARCH_TREE_OFFSET_Y);
	Vector2D scienceTreeUIOffset = Vector2D(SCIENCE_TREE_OFFSET_X, SCIENCE_TREE_OFFSET_Y);
	Vector2D treeUIButtonOffset1 = Vector2D(TREE_UI_BUTTON_OFFSET_1_X, TREE_UI_BUTTON_OFFSET_1_Y);
	Vector2D treeUIButtonOffset2 = Vector2D(TREE_UI_BUTTON_OFFSET_2_X, TREE_UI_BUTTON_OFFSET_2_Y);
	Vector2D treeUIButtonOffset3 = Vector2D(TREE_UI_BUTTON_OFFSET_3_X, TREE_UI_BUTTON_OFFSET_3_Y);
	Vector2D treeUIButtonOffset4 = Vector2D(TREE_UI_BUTTON_OFFSET_4_X, TREE_UI_BUTTON_OFFSET_4_Y);
	Vector2D treeUIButtonOffset5 = Vector2D(TREE_UI_BUTTON_OFFSET_5_X, TREE_UI_BUTTON_OFFSET_5_Y);
	Vector2D treeUIButtonOffset6 = Vector2D(TREE_UI_BUTTON_OFFSET_6_X, TREE_UI_BUTTON_OFFSET_6_Y);
	Vector2D treeUIButtonOffset7 = Vector2D(TREE_UI_BUTTON_OFFSET_7_X, TREE_UI_BUTTON_OFFSET_7_Y);
	Vector2D treeUIButtonOffset8 = Vector2D(TREE_UI_BUTTON_OFFSET_8_X, TREE_UI_BUTTON_OFFSET_8_Y);
	Vector2D treeUIButtonOffset9 = Vector2D(TREE_UI_BUTTON_OFFSET_9_X, TREE_UI_BUTTON_OFFSET_9_Y);
	Vector2D scienceUIButtonOffset1 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_1_X, SCIENCE_UI_BUTTON_OFFSET_1_Y);
	Vector2D scienceUIButtonOffset2 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_2_X, SCIENCE_UI_BUTTON_OFFSET_2_Y);
	Vector2D scienceUIButtonOffset3 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_3_X, SCIENCE_UI_BUTTON_OFFSET_3_Y);
	Vector2D scienceUIButtonOffset4 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_4_X, SCIENCE_UI_BUTTON_OFFSET_4_Y);
	Vector2D scienceUIButtonOffset5 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_5_X, SCIENCE_UI_BUTTON_OFFSET_5_Y);
	Vector2D scienceUIButtonOffset6 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_6_X, SCIENCE_UI_BUTTON_OFFSET_6_Y);
	Vector2D scienceUIButtonOffset7 = Vector2D(SCIENCE_UI_BUTTON_OFFSET_7_X, SCIENCE_UI_BUTTON_OFFSET_7_Y);

	Vector2D currencyUILoc = Vector2D(GAME_DISPLAY_WIDTH + CURRENCY_UI_HORIZONTAL_OFFSET, GAME_DISPLAY_HEIGHT - CURRENCY_UI_VERTICAL_OFFSET);
	Vector2D scienceUILoc = Vector2D(GAME_DISPLAY_WIDTH + SCIENCE_UI_HORIZONTAL_OFFSET, GAME_DISPLAY_HEIGHT - SCIENCE_UI_VERTICAL_OFFSET);

	Vector2D windowScale = Vector2D(WINDOW_SCALE);
	Vector2D buttonScale = Vector2D(BUTTON_SCALE);
	Vector2D treeButtonScale = Vector2D(TREE_BUTTON_SCALE);
	Vector2D subTreeButtonScale = Vector2D(SUB_TREE_BUTTON_SCALE);
	Vector2D baseTreeScale = Vector2D(BASE_TREE_SCALE);
	Vector2D scienceTreeScale = Vector2D(SCIENCE_TREE_SCALE);
	Vector2D scienceButtonScale = Vector2D(SCIENCE_BUTTON_SCALE);

	UIElement* shopUI = mpUIManager->createAndAddUIElement(SHOP_UI_FILEPATH, "shopUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, firstWindowUILoc, windowScale);
	mpUIManager->createAndAddUIElement(SHOP_UI_BUTTON_FILEPATH, "shopButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, shopButtonUILoc, buttonScale, shopUI, true);

	SyringeButton* purpleSyringeButton = new SyringeButton(ChickenColor::PURPLE, PURPLE_SYRINGE_BUTTON_FILEPATH, "PurpleSyringeButton", purpleSyringeButtonLoc, Vector2D::One(), shopUI);
	mpUIManager->addUIElement(purpleSyringeButton);
	SyringeButton* blackSyringeButton = new SyringeButton(ChickenColor::BLACK, BLACK_SYRINGE_BUTTON_FILEPATH, "BlackSyringeButton", blackSyringeButtonLoc, Vector2D::One(), shopUI);
	mpUIManager->addUIElement(blackSyringeButton);
	SyringeButton* blueSyringeButton = new SyringeButton(ChickenColor::BLUE, BLUE_SYRINGE_BUTTON_FILEPATH, "BlueSyringeButton", blueSyringeButtonLoc, Vector2D::One(), shopUI);
	mpUIManager->addUIElement(blueSyringeButton);
	SyringeButton* lightBlueSyringeButton = new SyringeButton(ChickenColor::LIGHT_BLUE, LIGHT_BLUE_SYRINGE_BUTTON_FILEPATH, "LightBlueSyringeButton", lightBlueSyringeButtonLoc, Vector2D::One(), shopUI);
	mpUIManager->addUIElement(lightBlueSyringeButton);
	SyringeButton* greenSyringeButton = new SyringeButton(ChickenColor::GREEN, GREEN_SYRINGE_BUTTON_FILEPATH, "GreenSyringeButton", greenSyringeButtonLoc, Vector2D::One(), shopUI);
	mpUIManager->addUIElement(greenSyringeButton);
	SyringeButton* yellowSyringeButton = new SyringeButton(ChickenColor::YELLOW, YELLOW_SYRINGE_BUTTON_FILEPATH, "YellowSyringeButton", yellowSyringeButtonLoc, Vector2D::One(), shopUI);
	mpUIManager->addUIElement(yellowSyringeButton);
	SyringeButton* redSyringeButton = new SyringeButton(ChickenColor::RED, RED_SYRINGE_BUTTON_FILEPATH, "RedSyringeButton", redSyringeButtonLoc, Vector2D::One(), shopUI);
	mpUIManager->addUIElement(redSyringeButton);

	UIElement* coopUI = mpUIManager->createAndAddUIElement(COOP_UI_FILEPATH, "coopUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, firstWindowUILoc, windowScale);
	mpUIManager->createAndAddUIElement(COOP_UI_BUTTON_FILEPATH, "coopButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, coopButtonUILoc, buttonScale, coopUI, true);
	mpUIManager->createAndAddUIElement(BASE_RESEARCH_TREE_FILEPATH, "baseResearchTreeUI", firstWindowUILoc + reserachTreeUIOffset, baseTreeScale, coopUI);
	mpUIManager->createAndAddUIElement(COOP_TREE_BUTTON_FILEPATH, "coopTreeButtonUI1", firstWindowUILoc + treeUIButtonOffset1, treeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "coopTreeButtonUI2", firstWindowUILoc + treeUIButtonOffset2, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "coopTreeButtonUI3", firstWindowUILoc + treeUIButtonOffset3, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "coopTreeButtonUI4", firstWindowUILoc + treeUIButtonOffset4, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "coopTreeButtonUI5", firstWindowUILoc + treeUIButtonOffset5, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "coopTreeButtonUI6", firstWindowUILoc + treeUIButtonOffset6, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "coopTreeButtonUI7", firstWindowUILoc + treeUIButtonOffset7, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "coopTreeButtonUI8", firstWindowUILoc + treeUIButtonOffset8, subTreeButtonScale, coopUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "coopTreeButtonUI9", firstWindowUILoc + treeUIButtonOffset9, subTreeButtonScale, coopUI);

	UIElement* penUI = mpUIManager->createAndAddUIElement(PEN_UI_FILEPATH, "penUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, firstWindowUILoc, windowScale);
	mpUIManager->createAndAddUIElement(PEN_UI_BUTTON_FILEPATH, "penButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, penButtonUILoc, buttonScale, penUI, true);
	mpUIManager->createAndAddUIElement(BASE_RESEARCH_TREE_FILEPATH, "baseResearchTreeUI", firstWindowUILoc + reserachTreeUIOffset, baseTreeScale, penUI);
	mpUIManager->createAndAddUIElement(PEN_TREE_BUTTON_FILEPATH, "penTreeButtonUI1", firstWindowUILoc + treeUIButtonOffset1, treeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "penTreeButtonUI2", firstWindowUILoc + treeUIButtonOffset2, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "penTreeButtonUI3", firstWindowUILoc + treeUIButtonOffset3, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "penTreeButtonUI4", firstWindowUILoc + treeUIButtonOffset4, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "penTreeButtonUI5", firstWindowUILoc + treeUIButtonOffset5, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "penTreeButtonUI6", firstWindowUILoc + treeUIButtonOffset6, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "penTreeButtonUI7", firstWindowUILoc + treeUIButtonOffset7, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "penTreeButtonUI8", firstWindowUILoc + treeUIButtonOffset8, subTreeButtonScale, penUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "penTreeButtonUI9", firstWindowUILoc + treeUIButtonOffset9, subTreeButtonScale, penUI);

	UIElement* hatcheryUI = mpUIManager->createAndAddUIElement(HATCHERY_UI_FILEPATH, "hatcheryUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, secondWindowUILoc, windowScale);
	mpUIManager->createAndAddUIElement(HATCHERY_UI_BUTTON_FILEPATH, "hatcheryButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, hatcheryButtonUILoc, buttonScale, hatcheryUI, true);
	mpUIManager->createAndAddUIElement(BASE_RESEARCH_TREE_FILEPATH, "baseResearchTreeUI", firstWindowUILoc + reserachTreeUIOffset, baseTreeScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(HATCHERY_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI1", firstWindowUILoc + treeUIButtonOffset1, treeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI2", firstWindowUILoc + treeUIButtonOffset2, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI3", firstWindowUILoc + treeUIButtonOffset3, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI4", firstWindowUILoc + treeUIButtonOffset4, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI5", firstWindowUILoc + treeUIButtonOffset5, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI6", firstWindowUILoc + treeUIButtonOffset6, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI7", firstWindowUILoc + treeUIButtonOffset7, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI8", firstWindowUILoc + treeUIButtonOffset8, subTreeButtonScale, hatcheryUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "hatcheryTreeButtonUI9", firstWindowUILoc + treeUIButtonOffset9, subTreeButtonScale, hatcheryUI);

	UIElement* scienceWindowUI = mpUIManager->createAndAddUIElement(SCIENCE_UI_FILEPATH, "scienceWindowUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, secondWindowUILoc, windowScale);
	mpUIManager->createAndAddUIElement(SCIENCE_UI_BUTTON_FILEPATH, "scienceButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, scienceButtonUILoc, buttonScale, scienceWindowUI, true);

	UIElement* scienceWindowScrollUI = (UIElement*)mpUIManager->createAndAddUIScrollElement(SCROLL_WINDOW_INSET, SCROLL_WINDOW_SPEED, "ScienceWindowScrollUI", Vector2D::Zero(), Vector2D::One(), scienceWindowUI);

	mpUIManager->createAndAddUIElement(SCIENCE_RESEARCH_TREE_FILEPATH, "scienceResearchTreeUI", firstWindowUILoc + scienceTreeUIOffset, scienceTreeScale, scienceWindowScrollUI);
	mpUIManager->createAndAddUIElement(RED_SYRINGE_TREE_BUTTON_FILEPATH, "redSyringeButtonUI", firstWindowUILoc + scienceUIButtonOffset1, subTreeButtonScale, scienceWindowScrollUI);
	mpUIManager->createAndAddUIElement(ADVANCED_TREE_BUTTON_FILEPATH, "scienceTreeButtonUI2", firstWindowUILoc + scienceUIButtonOffset2, subTreeButtonScale, scienceWindowScrollUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "scienceTreeButtonUI3", firstWindowUILoc + scienceUIButtonOffset3, subTreeButtonScale, scienceWindowScrollUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "scienceTreeButtonUI4", firstWindowUILoc + scienceUIButtonOffset4, subTreeButtonScale, scienceWindowScrollUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "scienceTreeButtonUI5", firstWindowUILoc + scienceUIButtonOffset5, subTreeButtonScale, scienceWindowScrollUI);
	mpUIManager->createAndAddUIElement(BASIC_TREE_BUTTON_FILEPATH, "scienceTreeButtonUI6", firstWindowUILoc + scienceUIButtonOffset6, subTreeButtonScale, scienceWindowScrollUI);
	mpUIManager->createAndAddUIElement(SCIENCE_TREE_BUTTON_FILEPATH, "scienceTreeButtonUI7", firstWindowUILoc + scienceUIButtonOffset7, scienceButtonScale, scienceWindowScrollUI);

	UIElement* settingsUI = mpUIManager->createAndAddUIElement(SETTINGS_UI_FILEPATH, "settingsUI", Direction::Up, BASE_WINDOW_UI_MOVE_DISTANCE, BASE_WINDOW_UI_ANIMATION_SPEED, secondWindowUILoc, windowScale);
	mpUIManager->createAndAddUIElement(SETTINGS_UI_BUTTON_FILEPATH, "settingsButtonUI", Direction::Up, BASE_BUTTON_UI_MOVE_DISTANCE, BASE_BUTTON_UI_ANIMATION_SPEED, settingsButtonUILoc, buttonScale, settingsUI, true);

	mpUIManager->createAndAddUIElement(MONEY_UI_FILEPATH, "currencyUI", Direction::Left, CURRENCY_UI_MOVE_DISTANCE, CURRENCY_UI_ANIMATION_SPEED, currencyUILoc, Vector2D::One(), nullptr, true);
	mpUIManager->createAndAddUIElement(SCIENCE_COUNT_UI_FILEPATH, "scienceUI", Direction::Left, SCIENCE_UI_MOVE_DISTANCE, SCIENCE_UI_ANIMATION_SPEED, scienceUILoc, Vector2D::One(), nullptr, true);

	mpGraphicsSystem->createAndAddFont("arial", "Resource Files/Fonts/arial.ttf", 20);

	mTimePerFrame = 1.0f / mFPS;
	mDeltaTime = 0.0f;
	mpTimer = new Timer();

	ifstream versionFile = ifstream("buildInfo.dat");
	if (!versionFile.is_open())
	{
		mpGraphicsSystem->addPersistantToDebugHUD("Version: Debug");
	}
	else
	{
		string version;
		versionFile >> version;
		mpGraphicsSystem->addPersistantToDebugHUD("Version: " + version);
	}

	mCurrentMoney = 300;

	mpGameListener = new GameListener();

	EventSystem::getInstance()->addListener(Event::MOUSE_EVENT, mpGameListener);
	EventSystem::getInstance()->addListener(Event::KEYBOARD_EVENT, mpGameListener);
	EventSystem::getInstance()->addListener((Event::EventType)GameEvent::CHICKEN_CLICK_EVENT, mpGameListener);

	srand(time(NULL));
}

void Game::initShaderObjects()
{
	mpGraphicsSystem->createAndAddShader("Textured Vert", VERTEX_SHADER, "textured.vert");
	mpGraphicsSystem->createAndAddShader("Textured Frag", FRAGMENT_SHADER, "textured.frag");
	mpGraphicsSystem->createAndAddShader("Basic Vert", VERTEX_SHADER, "basic.vert");
	mpGraphicsSystem->createAndAddShader("Basic UI Vert", VERTEX_SHADER, "basicUI.vert");
	mpGraphicsSystem->createAndAddShader("Color Frag", FRAGMENT_SHADER, "color.frag");
	mpGraphicsSystem->createAndAddShader("Text Vert", VERTEX_SHADER, "text.vert");
	mpGraphicsSystem->createAndAddShader("Text Frag", FRAGMENT_SHADER, "text.frag");

	mpGraphicsSystem->createAndAddShader("Textured Bounded Vert", VERTEX_SHADER, "texturedBounded.vert");
	mpGraphicsSystem->createAndAddShader("Textured Bounded Frag", FRAGMENT_SHADER, "texturedBounded.frag");

	mpGraphicsSystem->createAndAddShader("Chicken Color", FRAGMENT_SHADER, "chickenColor.frag");
}

void Game::initShaderPrograms()
{
	mpGraphicsSystem->createAndAddShaderProgram("Textured", "Textured Vert", "Textured Frag");
	mpGraphicsSystem->linkShaderProgram("Textured");
	mpGraphicsSystem->activateFloatAttributeOnProgram("Textured", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	mpGraphicsSystem->createAndAddShaderProgram("Color", "Basic Vert", "Color Frag");
	mpGraphicsSystem->linkShaderProgram("Color");
	mpGraphicsSystem->activateFloatAttributeOnProgram("Color", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	mpGraphicsSystem->createAndAddShaderProgram("ColorUI", "Basic UI Vert", "Color Frag");
	mpGraphicsSystem->linkShaderProgram("ColorUI");
	mpGraphicsSystem->activateFloatAttributeOnProgram("ColorUI", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	mpGraphicsSystem->createAndAddShaderProgram("Text", "Text Vert", "Text Frag");
	mpGraphicsSystem->linkShaderProgram("Text");

	mpGraphicsSystem->createAndAddShaderProgram("Textured Bounded", "Textured Bounded Vert", "Textured Bounded Frag");
	mpGraphicsSystem->linkShaderProgram("Textured Bounded");
	mpGraphicsSystem->activateFloatAttributeOnProgram("Textured Bounded", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	mpGraphicsSystem->createAndAddShaderProgram("ChickenColor", "Textured Vert", "Chicken Color");
	mpGraphicsSystem->linkShaderProgram("ChickenColor");
	mpGraphicsSystem->activateFloatAttributeOnProgram("ChickenColor", 0, 3); //Sets Attribute 0 to a 3 dimentional float value
	mpGraphicsSystem->activateFloatAttributeOnProgram("ChickenColor", 1, 3); //Sets Attribute 1 to a 3 dimentional float value
	mpGraphicsSystem->activateFloatAttributeOnProgram("ChickenColor", 2, 2); //Sets Attribute 2 to a 2 dimentional float value

	mpGraphicsSystem->setActiveShaderProgram("Textured");
}

void Game::cleanup()
{
	mpUIManager->cleanup();
	UIManager::cleanupInstance();
	mpUIManager = nullptr;

	mpChickenManager->cleanup();
	ChickenManager::cleanupInstance();
	mpChickenManager = nullptr;

	delete mpTimer;
	mpTimer = nullptr;

	InputSystem::cleanupInstance();
	
	delete mpGameListener;
	EventSystem::cleanupInstance();

	mpGraphicsSystem->cleanup();
	GraphicsSystem::cleanupInstance();
	mpGraphicsSystem = nullptr;
}

void Game::play()
{
	bool shouldContinue;

	do
	{
		shouldContinue = gameLoop();
	} while (shouldContinue);
}

bool Game::gameLoop()
{

	input();
	update();
	bool result = render();

	mpTimer->sleepUntilElapsed(mTimePerFrame * 1000);
	mDeltaTime = mpTimer->getElapsedTime();
	//cout << "Delta Time: " << mDeltaTime << endl;
	mpTimer->start();

	return result;
}

void Game::input()
{
	mpInputSystem->update();
}

void Game::update()
{
	mpGraphicsSystem->update(mDeltaTime);

	mpChickenManager->update(mDeltaTime);

	mpUIManager->update(mDeltaTime);

	Vector2D moneyTextOffset = Vector2D(MONEY_TEXT_HORIZONTAL_OFFSET, MONEY_TEXT_VERTICAL_OFFSET);
	mpGraphicsSystem->draw("$: " + to_string(mCurrentMoney), "arial", "Text", mpGraphicsSystem->getDisplayResolution() - moneyTextOffset,
		Vector3D::Up());

	int fps = debugGetFPS();
	if(fps != -1)
		mpGraphicsSystem->addToDebugHUD("FPS: " + to_string(debugGetFPS()));

	//Vector2D mousePos = mpInputSystem->getMousePosition();
	//mpGraphicsSystem->addToDebugHUD("Mouse Position: " + mousePos.toString());
	mpGraphicsSystem->addToDebugHUD("Camera Position: " + mpGraphicsSystem->getCamera()->getLoc().toString());

	mpGraphicsSystem->setIntegerUniform("Textured", "uTexture0", 0);
	mpGraphicsSystem->setVec2Uniform("Textured", "uResolution", mpGraphicsSystem->getDisplayResolution());
	mpGraphicsSystem->setVec2Uniform("Textured Bounded", "uResolution", mpGraphicsSystem->getDisplayResolution());
	mpGraphicsSystem->setVec2Uniform("Color", "uResolution", mpGraphicsSystem->getDisplayResolution());
	mpGraphicsSystem->setVec2Uniform("Text", "uResolution", mpGraphicsSystem->getDisplayResolution());
	mpGraphicsSystem->setIntegerUniform("ChickenColor", "uTexture0", 0);
	mpGraphicsSystem->setVec2Uniform("ChickenColor", "uResolution", mpGraphicsSystem->getDisplayResolution());
}

bool Game::render()
{
	string previousShader;

	mpGraphicsSystem->setActiveShaderProgram("ChickenColor");

	mpChickenManager->drawAllChickens();

	mpGraphicsSystem->setActiveShaderProgram("Textured");

	if (mpSelectedChicken)
	{
		if (mpChickenSelectionMesh && mpChickenSelectionMesh->getVertexAt(3).getX() != mpSelectedChicken->getSize().getX())
		{
			delete mpChickenSelectionMesh;
			mpChickenSelectionMesh = nullptr;
		}

		if (!mpChickenSelectionMesh)
		{
			int pixelWidth = mpSelectedChicken->getSize().getX();

			Vector2D verticies[4] = {Vector2D(0,0), Vector2D(0,pixelWidth), Vector2D(pixelWidth,0), Vector2D(pixelWidth,pixelWidth)};
			unsigned int drawOrder[6] = {0, 1, 2, 1, 2, 3};
			mpChickenSelectionMesh = new Mesh2D(verticies, 4, drawOrder, 6);
		}

		previousShader = mpGraphicsSystem->getCurrentShaderProgram();
		GraphicsSystem::DrawMode previousDrawMode = mpGraphicsSystem->getDrawMode();

		mpGraphicsSystem->setActiveShaderProgram("Color");

		Vector4D green = Vector4D(0.0f, 1.0f, 0.0f, 1.0f);
		mpGraphicsSystem->setVec4Uniform("Color", "uColor", green);

		mpGraphicsSystem->setDrawMode(GraphicsSystem::DrawMode::Wireframe);
		mpGraphicsSystem->draw(*mpChickenSelectionMesh);
		mpGraphicsSystem->setActiveShaderProgram(previousShader);
		mpGraphicsSystem->setDrawMode(previousDrawMode);
	}


	previousShader = mpGraphicsSystem->getCurrentShaderProgram();
	mpGraphicsSystem->setActiveShaderProgram("Textured Bounded");
	mpUIManager->draw();
	mpGraphicsSystem->setActiveShaderProgram(previousShader);

	mpGraphicsSystem->draw("Hello World!", "arial", "Text", Vector2D(50, 50));

	return mpGraphicsSystem->render();
}

void Game::checkChickenClicked(Vector2D mousePos, MouseAction mouseButton)
{
	GridSystem* grs = GridSystem::getInstance();
	Chicken* clickedChicken = mpChickenManager->checkChickenHovered(grs->convertPixelsToGrid(mousePos));
	EventSystem* es = EventSystem::getInstance();

	if (mpGameCursor && mouseButton == MouseAction::LeftClick)
	{
		if (clickedChicken)
			clickedChicken->paintEgg(mpGameCursor->getSyringeColor());

		delete mpGameCursor;
		mpGameCursor = nullptr;
		mpUIManager->setCursor(nullptr);
		mpGraphicsSystem->setCursorHidden(false);
	}

	if (clickedChicken)
	{
		
		ChickenClickEvent cknEvent(clickedChicken, mouseButton);
		es->fireEvent(cknEvent);
	}
}

void Game::onChickenLeftClick(Chicken* ckn)
{
	if (mDebugMode)
	{

		if (mpSelectedChicken)
		{
			mpSelectedChicken->setDebugMode(false);
		}

		mpSelectedChicken = ckn;
		mpSelectedChicken->setDebugMode(true);
	}
	else
		ckn->onMouseClick();
}

void Game::onChickenRightClick(Chicken* ckn)
{
	if (!mDebugMode)
	{
		if (ckn->isEgg())
		{
			mCurrentMoney += Chicken::GetSellAmount(ckn);

			mpChickenManager->removeAndDeleteChicken(ckn);
		}
	}
}

void Game::moveDebugChicken(Vector2D mousePos)
{
	if (mpSelectedChicken && mDebugMode)
	{
		mpSelectedChicken->moveToLocation(mousePos);
	}
}

void Game::startMouseDrag(Vector2D mousePos)
{
	mpGraphicsSystem->getCamera()->startMouseDrag(mousePos);
}

void Game::stopMouseDrag()
{
	mpGraphicsSystem->getCamera()->stopMouseDrag();
}

void Game::onMouseMove(Vector2D mousePos)
{
	//Should probably merge these functions into one
	mpUIManager->onMouseHover(mousePos);
	mpUIManager->updateCursorPosition(mousePos);

	mpGraphicsSystem->getCamera()->update(mousePos);
}

void Game::onToggleDrawMode()
{
	switch (mpGraphicsSystem->getDrawMode())
	{
	case GraphicsSystem::DrawMode::Fill:
		mpGraphicsSystem->setDrawMode(GraphicsSystem::DrawMode::Wireframe);
		break;

	case GraphicsSystem::DrawMode::Wireframe:
		mpGraphicsSystem->setDrawMode(GraphicsSystem::DrawMode::Fill);
		break;
	}
}

void Game::onToggleShaders()
{
	if (mpGraphicsSystem->getCurrentShaderProgram() == "Textured")
	{
		mpGraphicsSystem->setActiveShaderProgram("Color");
		Vector4D green = Vector4D(0.0f, 1.0f, 0.0f, 1.0f);
		mpGraphicsSystem->setVec4Uniform("Color", "uColor", green);
	}
	else
		mpGraphicsSystem->setActiveShaderProgram("Textured");
}

void Game::onShaderHotReload()
{
	//Hot Reload Shaders... Should probably do this through the managers (to not add a line for every new shader)
	mpGraphicsSystem->reloadShader("Textured Vert");
	mpGraphicsSystem->reloadShader("Textured Frag");
	mpGraphicsSystem->reloadShader("Basic Vert");
	mpGraphicsSystem->reloadShader("Color Frag");

	mpGraphicsSystem->linkShaderProgram("Textured");
	mpGraphicsSystem->linkShaderProgram("Color");
}

void Game::onToggleDebugMode()
{
	mDebugMode = !mDebugMode;

	if (mpSelectedChicken && !mDebugMode)
	{
		mpSelectedChicken->setDebugMode(false);
		mpSelectedChicken = nullptr;
	}

	mpGraphicsSystem->setDebugMode(mDebugMode);
}

bool Game::checkUIClicked(const MouseEvent event)
{
	if (event.getButtonState() == ButtonState::Down)
	{
		return mpUIManager->onClick(event.getMousePosition());
	}
}

void Game::setMouseToSyringe(ChickenColor color, Vector2D mousePos)
{
	if (mpGameCursor)
	{
		delete mpGameCursor;
		mpGameCursor = nullptr;
		mpUIManager->setCursor(nullptr);
	}
		
	
	mpGameCursor = new GameCursor(color);
	mpGameCursor->setLoc(mousePos);

	switch (color)
	{
	case ChickenColor::PURPLE:
		mpGameCursor->setImage(mpGraphicsSystem->getSprite(PURPLE_SYRINGE_KEY));
		break;
	case ChickenColor::BLACK:
		mpGameCursor->setImage(mpGraphicsSystem->getSprite(BLACK_SYRINGE_KEY));
		break;
	case ChickenColor::BLUE:
		mpGameCursor->setImage(mpGraphicsSystem->getSprite(BLUE_SYRINGE_KEY));
		break;
	case ChickenColor::LIGHT_BLUE:
		mpGameCursor->setImage(mpGraphicsSystem->getSprite(LIGHT_BLUE_SYRINGE_KEY));
		break;
	case ChickenColor::GREEN:
		mpGameCursor->setImage(mpGraphicsSystem->getSprite(GREEN_SYRINGE_KEY));
		break;
	case ChickenColor::YELLOW:
		mpGameCursor->setImage(mpGraphicsSystem->getSprite(YELLOW_SYRINGE_KEY));
		break;
	case ChickenColor::RED:
		mpGameCursor->setImage(mpGraphicsSystem->getSprite(RED_SYRINGE_KEY));
		break;
	}

	mpUIManager->setCursor(mpGameCursor);
	mpGraphicsSystem->setCursorHidden(true);
}

void Game::onClick(const MouseEvent event)
{
	if(checkUIClicked(event))
		return;

	if (event.getMouseAction() == MouseAction::RightClick || event.getMouseAction() == MouseAction::LeftClick)
		checkChickenClicked(event.getMousePosition(), event.getMouseAction());

	if (event.getMouseAction() == MouseAction::RightClick && event.getButtonState() == ButtonState::Down)
		moveDebugChicken(event.getMousePosition());



	if (event.getMouseAction() == MouseAction::MiddleClick)
	{
		if (event.getButtonState() == ButtonState::Down)
			startMouseDrag(event.getMousePosition());
		else if (event.getButtonState() == ButtonState::Up)
			stopMouseDrag();
	}

}

bool Game::buySyringe(ChickenColor color, Vector2D mousePos, int cost)
{
	if (mCurrentMoney >= cost)
	{
		setMouseToSyringe(color, mousePos);
		mCurrentMoney -= cost;
		return true;
	}
	else
		return false;
}
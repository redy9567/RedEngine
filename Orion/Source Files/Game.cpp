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
#include "UIElement.h"
#include "Camera2D.h"
#include "Vector4D.h"
#include "EventSystem.h"
#include "GameEvents.h"
#include "GridSystem.h"
#include "UIManager.h"
#include "Filepaths.h"
#include "Vector2D.h"
#include <fstream>
#include "Physics.h"

#include <assert.h>
#include <iostream>

using namespace std;

Game* Game::mspInstance = nullptr;

const Vector2D circleStartLoc = Vector2D(21.5f, 11.0f);
const Vector2D rodStartLoc = Vector2D(21.5f, 22.0f);

const Vector2D circleStartLoc3 = Vector2D(21.5f, 18.0f);

const float pi = 3.14159265358979323846f;

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

	mpBuildingHighlight = nullptr;

	mCurrentScene = 0;

	mPendulumAngleVelocity = 0.0f;
	mPendulumAngle = 0.0f;

	mPendulumAngleAcceleration = 0.0f;
	mPendulum2Angle = 0.0f;
	mPendulum2AngleVelocity = 0.0f;
	mPendulum2AngleAcceleration = 0.0f;
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

	loadData();

	mpGraphicsSystem->setBackgroundColor(Vector3D(0.7f, 0.7f, 0.7f));

	Texture2D* circleTexture = mpGraphicsSystem->createAndAddTexture2D("circle", RESOURCES_DIRECTORY + "circle.png", true);
	Texture2D* squareTexture = mpGraphicsSystem->createAndAddTexture2D("square", RESOURCES_DIRECTORY + "square.png", false);

	Vector2D originScale = Vector2D(0.01f, 0.01f);

	Sprite* originSprite = mpGraphicsSystem->createAndAddSprite("origin", &circleTexture, Vector2D::Zero(), squareTexture->getSize(), originScale);

	mOriginObj = mpGraphicsSystem->createGameObject2D(originSprite, circleStartLoc);

	mCurrentScene = 1;
	initScene1();

	mpUIManager = UIManager::getInstance();
	mpUIManager->init();

	
	mpGraphicsSystem->createAndAddFont("arial", "Resource Files/Fonts/arial.ttf", 34);

	mTimePerFrame = 1.0f / mFPS;
	mDeltaTime = 0.0f;
	mRunningTime = 0.0f;
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

	EventSystem::getInstance()->addListener(Event::EventType::KEYBOARD_EVENT, (EventListener*) & mListener);

	srand(time(NULL));
}

void Game::loadData()
{
	//Texture2D* tex = mpGraphicsSystem->createAndAddTexture2D("ScienceBuilding", SCIENCE_BUILDING_FILEPATH, true);
	//mpGraphicsSystem->createAndAddSprite("ScienceBuilding", &tex, Vector2D::Zero(), tex->getSize());
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

	mpGraphicsSystem->setActiveShaderProgram("Textured");
}

void Game::cleanup()
{
	cleanupCurrentScene();

	mpUIManager->cleanup();
	UIManager::cleanupInstance();
	mpUIManager = nullptr;

	delete mpTimer;
	mpTimer = nullptr;

	InputSystem::cleanupInstance();
	
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
	mRunningTime += mDeltaTime;
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
	switch (mCurrentScene)
	{
	case 1:
		updateScene1();
		break;

	case 2:
		updateScene2();
		break;

	case 3:
		updateScene3();
	}
	
	mpGraphicsSystem->update(mDeltaTime);

	mpUIManager->update(mDeltaTime);

	int fps = debugGetFPS();
	if(fps != -1)
		mpGraphicsSystem->addToDebugHUD("FPS: " + to_string(debugGetFPS()));

	//Vector2D mousePos = mpInputSystem->getMousePosition();
	//mpGraphicsSystem->addToDebugHUD("Mouse Position: " + mousePos.toString());
	mpGraphicsSystem->addToDebugHUD("Camera Position: " + mpGraphicsSystem->getCamera()->getLoc().toString());

	mpGraphicsSystem->setIntegerUniform("Textured", "uTexture0", 0);
	mpGraphicsSystem->setVec2Uniform("Textured", "uResolution", mpGraphicsSystem->getCamera()->getResolution());
	mpGraphicsSystem->setVec2Uniform("Textured Bounded", "uResolution", mpGraphicsSystem->getCamera()->getResolution());
	mpGraphicsSystem->setVec2Uniform("Color", "uResolution", mpGraphicsSystem->getCamera()->getResolution());
	mpGraphicsSystem->setVec2Uniform("Text", "uResolution", mpGraphicsSystem->getCamera()->getResolution());
	mpGraphicsSystem->setVec2Uniform("ColorTextured", "uResolution", mpGraphicsSystem->getCamera()->getResolution());
}

bool Game::render()
{

	mpGraphicsSystem->setActiveShaderProgram("ColorTextured");

	mpGraphicsSystem->setVec4Uniform("ColorTextured", "uColor", Vector4D(0.0f, 0.0f, 0.0f, 1.0f));

	mpGraphicsSystem->draw(mOriginObj);

	mpGraphicsSystem->setVec4Uniform("ColorTextured", "uColor", Vector4D(1.0f, 0.0f, 0.0f, 1.0f));
	
	mpGraphicsSystem->drawInternalObjects();

	mpGraphicsSystem->setActiveShaderProgram("Textured");

	string previousShader = mpGraphicsSystem->getCurrentShaderProgram();
	mpGraphicsSystem->setActiveShaderProgram("Textured Bounded");
	mpUIManager->draw();
	mpGraphicsSystem->setActiveShaderProgram(previousShader);

	mpGraphicsSystem->drawUI("Coordinates: ", "arial", "Text", Vector2D(0.01f, 0.02f), Vector3D(0.0f, 0.0f, 0.0f));
	mpGraphicsSystem->drawUI((mCircleObj->getLoc() - circleStartLoc).toString(), "arial", "Text", Vector2D(0.15f, 0.02f), Vector3D(0.0f, 0.0f, 0.0f));

	if (mCurrentScene != 1)
	{
		mpGraphicsSystem->drawUI("Theta: ", "arial", "Text", Vector2D(0.01f, 0.06f), Vector3D(0.0f, 0.0f, 0.0f));
		mpGraphicsSystem->drawUI(to_string(mPendulumAngle), "arial", "Text", Vector2D(0.08f, 0.06f), Vector3D(0.0f, 0.0f, 0.0f));
	}

	return mpGraphicsSystem->render();
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

	mpGraphicsSystem->setDebugMode(mDebugMode);
}

void Game::initScene1()
{
	mCurrentScene = 1;

	Vector2D circleScale = Vector2D(0.05f, 0.05f);
	Vector2D rodScale = Vector2D(0.01f, 0.85f);
	
	Texture2D* squareTexture = mpGraphicsSystem->getTexture2D("square");
	Texture2D* circleTexture = mpGraphicsSystem->getTexture2D("circle");

	Sprite* squareSprite = mpGraphicsSystem->createAndAddSprite("square", &squareTexture, Vector2D::Zero(), squareTexture->getSize(), rodScale);
	Sprite* circleSprite = mpGraphicsSystem->createAndAddSprite("circle", &circleTexture, Vector2D::Zero(), circleTexture->getSize(), circleScale);
	
	mRodObj = mpGraphicsSystem->createAndAddGameObject2D(squareSprite, rodStartLoc);
	mCircleObj = mpGraphicsSystem->createAndAddGameObject2D(circleSprite, circleStartLoc);

	mRodObj->setRotation(0.0f);
}

void Game::cleanupScene1()
{
	mpGraphicsSystem->removeAndDeleteGameObject2D(mRodObj);
	mRodObj = nullptr;

	mpGraphicsSystem->removeAndDeleteGameObject2D(mCircleObj);
	mCircleObj = nullptr;

	mpGraphicsSystem->removeAndDeleteSprite("square");
	mpGraphicsSystem->removeAndDeleteSprite("circle");
}

void Game::updateScene1()
{
	mCircleObj->setLoc(circleStartLoc + Vector2D(smallAnglePendulumFunction(mRunningTime), 0.0f));
	mRodObj->setRotation(smallAnglePendulumAngle(mRunningTime));
}

void Game::initScene2()
{
	mCurrentScene = 2;

	Vector2D circleScale = Vector2D(0.05f, 0.05f);
	Vector2D rodScale = Vector2D(0.01f, 0.25f);

	Texture2D* squareTexture = mpGraphicsSystem->getTexture2D("square");
	Texture2D* circleTexture = mpGraphicsSystem->getTexture2D("circle");

	Sprite* squareSprite = mpGraphicsSystem->createAndAddSprite("square", &squareTexture, Vector2D::Zero(), squareTexture->getSize(), rodScale);
	Sprite* circleSprite = mpGraphicsSystem->createAndAddSprite("circle", &circleTexture, Vector2D::Zero(), circleTexture->getSize(), circleScale);

	mRodObj = mpGraphicsSystem->createAndAddGameObject2D(squareSprite, circleStartLoc, true);
	mCircleObj = mpGraphicsSystem->createAndAddGameObject2D(circleSprite, circleStartLoc);

	mPendulumAngle = 80.0f;
	mPendulumAngleVelocity = 0.0f;
	
}

void Game::cleanupScene2()
{
	mpGraphicsSystem->removeAndDeleteGameObject2D(mRodObj);
	mRodObj = nullptr;

	mpGraphicsSystem->removeAndDeleteGameObject2D(mCircleObj);
	mCircleObj = nullptr;

	mpGraphicsSystem->removeAndDeleteSprite("square");
	mpGraphicsSystem->removeAndDeleteSprite("circle");
}

void Game::updateScene2()
{

	float rod2LengthX = 7.0f;
	float rod2LengthY = 6.5f;

	mCircleObj->setLoc(circleStartLoc + Vector2D(sin(mPendulumAngle * pi / 180.0f) * rod2LengthX, -cos(mPendulumAngle * pi / 180.0f) * rod2LengthY));
	mRodObj->setRotation(mPendulumAngle);

	mPendulumAngleVelocity += singlePendulumAccelerationFunction(6.75f, mPendulumAngle) * mDeltaTime;
	mPendulumAngle += mPendulumAngleVelocity;
	
}

void Game::initScene3()
{
	mCurrentScene = 3;

	Vector2D circleScale = Vector2D(0.05f, 0.05f);
	Vector2D rodScale = Vector2D(0.01f, 0.25f);

	Texture2D* squareTexture = mpGraphicsSystem->getTexture2D("square");
	Texture2D* circleTexture = mpGraphicsSystem->getTexture2D("circle");

	Sprite* squareSprite = mpGraphicsSystem->createAndAddSprite("square", &squareTexture, Vector2D::Zero(), squareTexture->getSize(), rodScale);
	Sprite* circleSprite = mpGraphicsSystem->createAndAddSprite("circle", &circleTexture, Vector2D::Zero(), circleTexture->getSize(), circleScale);

	mRodObj = mpGraphicsSystem->createAndAddGameObject2D(squareSprite, circleStartLoc3, true);
	mCircleObj = mpGraphicsSystem->createAndAddGameObject2D(circleSprite, circleStartLoc3);

	mRod2Obj = mpGraphicsSystem->createAndAddGameObject2D(squareSprite, circleStartLoc3, true);
	mCircle2Obj = mpGraphicsSystem->createAndAddGameObject2D(circleSprite, circleStartLoc3);

	mPendulumAngle = 0.0f;
	mPendulumAngleVelocity = 0.0f;

	mPendulumAngleAcceleration = 0.0f;
	mPendulum2Angle = 30.0f;
	mPendulum2AngleVelocity = 0.0f;
	mPendulum2AngleAcceleration = 0.0f;

}

void Game::cleanupScene3()
{
	mpGraphicsSystem->removeAndDeleteGameObject2D(mRodObj);
	mRodObj = nullptr;

	mpGraphicsSystem->removeAndDeleteGameObject2D(mCircleObj);
	mCircleObj = nullptr;

	mpGraphicsSystem->removeAndDeleteGameObject2D(mRod2Obj);
	mRod2Obj = nullptr;

	mpGraphicsSystem->removeAndDeleteGameObject2D(mCircle2Obj);
	mCircle2Obj = nullptr;

	mpGraphicsSystem->removeAndDeleteSprite("square");
	mpGraphicsSystem->removeAndDeleteSprite("circle");
}

void Game::updateScene3()
{

	float rod2LengthX = 7.0f;
	float rod2LengthY = 6.5f;

	mCircleObj->setLoc(circleStartLoc3 + Vector2D(sin(mPendulumAngle * pi / 180.0f) * rod2LengthX, -cos(mPendulumAngle * pi / 180.0f) * rod2LengthY));
	mRodObj->setRotation(mPendulumAngle);

	mCircle2Obj->setLoc(mCircleObj->getLoc() + Vector2D(sin(mPendulum2Angle * pi / 180.0f) * rod2LengthX, -cos(mPendulum2Angle * pi / 180.0f) * rod2LengthY));
	mRod2Obj->setLoc(mCircleObj->getLoc());
	mRod2Obj->setRotation(mPendulum2Angle);

	float oldAcc1 = mPendulumAngleAcceleration;

	mPendulumAngleAcceleration = -doublePendulumFirstAccelerationFunction(1.0f, 1.0f, 6.75f, 6.75f, mPendulumAngle, mPendulum2Angle, mPendulum2AngleVelocity, mPendulum2AngleAcceleration) * mDeltaTime * 2;
	mPendulum2AngleAcceleration = -doublePendulumSecondAccelerationFunction(6.75f, 6.75f, mPendulumAngle, mPendulum2Angle, mPendulumAngleVelocity, oldAcc1) * mDeltaTime * 2;
	
	mPendulumAngleVelocity += mPendulumAngleAcceleration;
	mPendulum2AngleVelocity += mPendulum2AngleAcceleration;

	mPendulumAngle += mPendulumAngleVelocity;
	mPendulum2Angle += mPendulum2AngleVelocity;

}

void Game::cleanupCurrentScene()
{
	switch (mCurrentScene)
	{
	case 1:
		cleanupScene1();
		break;

	case 2:
		cleanupScene2();
		break;

	case 3:
		cleanupScene3();
	}
}

void Game::startScene1()
{
	cleanupCurrentScene();

	initScene1();
}

void Game::startScene2()
{
	cleanupCurrentScene();

	initScene2();
}

void Game::startScene3()
{
	cleanupCurrentScene();

	initScene3();
}
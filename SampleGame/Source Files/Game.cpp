#include "Game.h"
#include "GraphicsSystem.h"
#include "Color.h"
#include "Animation.h"
#include "AnimationData.h"
#include "Player.h"
#include "Timer.h"
#include "AnimationManager.h"
#include "EventSystem.h"
#include "GameObject2DManager.h"
#include "Texture2D.h"
#include "InputSystem.h"
#include "MouseEvent.h"
#include "GameListener.h"
#include "AxisEvent.h"
#include "Mesh3D.h"
#include "Camera3D.h"
#include "GameObject3D.h"

#include <iostream>
#include <Shader.h>
#include <cassert>

using namespace std;

const float CAMERA_MOVE_SPEED = 0.01f;
const float CAMERA_ROTATE_SPEED = 1.0f;

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

void Game::startGame()
{
	mIsPlaying = true;
	mpGameTimer->start();
	while (mIsPlaying)    // Detect window close button or ESC key
	{
		if(!mIsPaused)
			mDeltaTime = mpGameTimer->getElapsedTime();
		mTimeElapsed += mDeltaTime;
		mpGameTimer->start();

		getInput();
		update();
		render();

		debug();

		while(mpGameTimer->getElapsedTime() < mTimePerFrame)
			mpGameTimer->sleepUntilElapsed(mTimePerFrame);
			
	}
}

Game::Game()
{
	mpGraphicsSystem = nullptr;
	mpPlayerUnit = nullptr;
	mpGameTimer = nullptr;

	mDebugMode = false;
	mIsPlaying = false;
	mTimePerFrame = 0.0f;

	mDeltaTime = 0.0f;
	mTimeElapsed = 0.0f;
}

Game::~Game()
{
	
}

void Game::init(int screenWidth, int screenHeight, int fps, bool debugMode)
{

	mpGraphicsSystem = GraphicsSystem::getInstance();

	assert(mpGraphicsSystem->init(screenWidth, screenHeight));

	mpGraphicsSystem->setActiveShaderProgram("Basic3D");

	mpCube = new Mesh3D(PrimitiveType::Cube);
	mpPlane = new Mesh3D(PrimitiveType::Plane);
	mpSphere = new Mesh3D(PrimitiveType::Sphere);

	vector<string> skyboxFilepaths;
	skyboxFilepaths.push_back("Assets/skybox/right.jpg");
	skyboxFilepaths.push_back("Assets/skybox/left.jpg");
	skyboxFilepaths.push_back("Assets/skybox/top.jpg");
	skyboxFilepaths.push_back("Assets/skybox/bottom.jpg");
	skyboxFilepaths.push_back("Assets/skybox/front.jpg");
	skyboxFilepaths.push_back("Assets/skybox/back.jpg");

	mpGraphicsSystem->setSkybox(skyboxFilepaths);

	mpGameListener = new GameListener();
	EventSystem::getInstance()->addListener(Event::KEYBOARD_EVENT, mpGameListener);
	EventSystem::getInstance()->addListener(Event::MOUSE_EVENT, mpGameListener);
	EventSystem::getInstance()->addListener(Event::AXIS_EVENT, mpGameListener);

	mpGameTimer = new Timer();

	mTimePerFrame = 1.0f / fps;
	mDebugMode = debugMode;

	mpGraphicsSystem->setBackgroundColor(Vector3D(0.1f, 0.03f, 0.25f));

	mpGraphicsSystem->createAndAddGameObject3D(mpPlane, Vector3D(0.0f, -1.0f, -3.0f), Vector3D(0.0f, 0.5f, 0.0f), Vector3D(5.0f, 1.0f, 5.0f));

	const float SPIN_SPEED = 10.0f;

	mBall1 = mpGraphicsSystem->createAndAddGameObject3D(mpSphere, Vector3D(-1.0f, 0.0f, -2.0f), Vector3D(0.5f, 0.0f, 0.5f), Vector3D(0.5f, 0.5f, 0.5f));
	mBall1->enablePhysics();
	mBall1->getPhysics()->setVel(Vector3D(0.25f, 0.0f, 0.0f));
	mBall1->getPhysics()->setRotVel(Vector3D(0.13f, 0.75f, 0.48f) * SPIN_SPEED);

	mBall2 = mpGraphicsSystem->createAndAddGameObject3D(mpSphere, Vector3D(1.0f, 0.0f, -2.0f), Vector3D(0.0f, 0.5f, 0.5f), Vector3D(0.5f, 0.5f, 0.5f));
	mBall2->enablePhysics();
	mBall2->getPhysics()->setVel(Vector3D(-0.25f, 0.0f, 0.0f));
	mBall2->getPhysics()->setRotVel(Vector3D(0.83f, 0.13f, 0.74f) * SPIN_SPEED);
	
	mIsPaused = false;

	srand(time(NULL));
}

void Game::cleanup()
{
	delete mpGameListener;
	mpGameListener = nullptr;

	delete mpPlayerUnit;
	mpPlayerUnit = nullptr;

	EventSystem::cleanupInstance();

	mpGraphicsSystem->cleanup();

	GraphicsSystem::cleanupInstance();
	mpGraphicsSystem = nullptr;

	delete mpGameTimer;
	mpGameTimer = nullptr;
}

void Game::getInput()
{
	InputSystem::getInstance()->update();
}

void Game::update()
{
	//mpGraphicsSystem->setIntegerUniform("Textured", "uTexture0", 0);
	mpGraphicsSystem->setVec2Uniform("Textured", "uResolution", mpGraphicsSystem->getDisplayResolution());

	if (mpLine)
	{
		delete mpLine;
		mpLine = nullptr;
	}

	//Check for Collision Detection between the two spheres... (We are assuming the scale is uniform on all axes, using one as radius)
	if ((mBall1->getLoc() - mBall2->getLoc()).length() < mBall1->getScale().getX() + mBall2->getScale().getX())
	{
		//Collision!
		mBall1->setColor(Vector3D(1.0f, 0.0f, 0.0f));
		mBall2->setColor(Vector3D(1.0f, 0.0f, 0.0f));

		Vector3D collisionDir = (mBall2->getLoc() - mBall1->getLoc()).normalized();
		//Create a line on the surface of ball1, with the length of the penetration
		Vector3D surfacePoint = mBall1->getLoc() + (collisionDir * mBall1->getScale().getX());
		float penetrationLength = mBall1->getScale().getX() + mBall2->getScale().getX() - (mBall2->getLoc() - mBall1->getLoc()).length();
		mpLine = new Mesh3D(surfacePoint, surfacePoint + collisionDir * penetrationLength);
	}
	else
	{
		mBall1->setColor(Vector3D(0.5f, 0.0f, 0.5f));
		mBall2->setColor(Vector3D(0.0f, 0.5f, 0.5f));
	}

	//mpGraphicsSystem->getAnimation(0)->update(mDeltaTime);

	mpGraphicsSystem->update(mDeltaTime);
}

void Game::render()
{
	mpGraphicsSystem->drawInternalObjects();

	if (mpLine)
	{
		mpGraphicsSystem->setVec4Uniform("Basic3D", "uColor", Vector4D(1.0f, 1.0f, 0.0f, 1.0f));
		
		mpGraphicsSystem->setDrawLineWidth(4.0f);
		mpGraphicsSystem->draw(*mpLine, Vector3D::Zero());
		mpGraphicsSystem->setDrawLineWidth(1.0f);
	}

	mpGraphicsSystem->render();
}

void Game::debug()
{
	if(mDebugMode)
	{
		//cout << "Frame Length: " << mDeltaTime << ", which is equal to " << 1 / mDeltaTime << " FPS." << endl;
	}
}

void Game::DPlayerMove(Vector2D loc)
{
	cout << "Player move to: " << loc << endl;
}

void Game::DMousePress(int button)
{
	cout << "Mouse Button pressed with ID: " << button << endl;
}

void Game::DMouseRelease(int button)
{
	cout << "Mouse Button released with ID: " << button << endl;
}

void Game::quitGame()
{
	mIsPlaying = false;
	cout << "QUIT" << endl;
}

void Game::onMouseMove(Vector2D mouseLoc)
{

}

void Game::onClick(const MouseEvent& event)
{

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

void Game::onAxis(const AxisEvent& ev)
{
	mpPlayerUnit->setMoveDirection(ev.getState());
}

void Game::handleCameraMovement(KeyCode key)
{
	Camera3D* camera = mpGraphicsSystem->getCamera();
	Vector3D cameraLoc = camera->getLoc();
	Vector3D cameraRot = camera->getRotation();

	switch (key)
	{
	case KeyCode::A:
		camera->setLoc(cameraLoc + Vector3D(-CAMERA_MOVE_SPEED, 0.0f, 0.0f));
		break;

	case KeyCode::D:
		camera->setLoc(cameraLoc + Vector3D(CAMERA_MOVE_SPEED, 0.0f, 0.0f));
		break;

	case KeyCode::S:
		camera->setLoc(cameraLoc + Vector3D(0.0f, 0.0f, CAMERA_MOVE_SPEED));
		break;

	case KeyCode::W:
		camera->setLoc(cameraLoc + Vector3D(0.0f, 0.0f, -CAMERA_MOVE_SPEED));
		break;

	case KeyCode::E:
		camera->setLoc(cameraLoc + Vector3D(0.0f, CAMERA_MOVE_SPEED, 0.0f));
		break;

	case KeyCode::Q:
		camera->setLoc(cameraLoc + Vector3D(0.0f, -CAMERA_MOVE_SPEED, 0.0f));
		break;

	case KeyCode::O:
		camera->setRotation(cameraRot + Vector3D(0.0f, 0.0f, CAMERA_ROTATE_SPEED));
		break;

	case KeyCode::U:
		camera->setRotation(cameraRot + Vector3D(0.0f, 0.0f, -CAMERA_ROTATE_SPEED));
		break;

	case KeyCode::I:
		camera->setRotation(cameraRot + Vector3D(-CAMERA_ROTATE_SPEED, 0.0f, 0.0f));
		break;

	case KeyCode::K:
		camera->setRotation(cameraRot + Vector3D(CAMERA_ROTATE_SPEED, 0.0f, 0.0f));
		break;

	case KeyCode::J:
		camera->setRotation(cameraRot + Vector3D(0.0f, CAMERA_ROTATE_SPEED, 0.0f));
		break;

	case KeyCode::L:
		camera->setRotation(cameraRot + Vector3D(0.0f, -CAMERA_ROTATE_SPEED, 0.0f));
		break;
	}

}

void Game::onTogglePause()
{
	mIsPaused = !mIsPaused;

	if (mIsPaused)
		mDeltaTime = 0.0f;
}
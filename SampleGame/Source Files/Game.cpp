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
#include "Matrix3D.h"

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

	createPoolTable();

	const float SPIN_SPEED = 10.0f;
	
	GameObject3D* ball = mpGraphicsSystem->createAndAddGameObject3D(mpSphere, Vector3D(-1.0f, 0.0f, -2.0f), Vector3D(0.5f, 0.0f, 0.5f), Vector3D(0.225f, 0.225f, 0.225f));
	ball->enablePhysics();
	ball->getPhysics()->setVel(Vector3D(-4.0f, 0.0f, 0.0f));
	mPoolBalls.push_back(ball);
	//mBall1->getPhysics()->setRotVel(Vector3D(0.13f, 0.75f, 0.48f) * SPIN_SPEED);
	
	ball = mpGraphicsSystem->createAndAddGameObject3D(mpSphere, Vector3D(1.0f, 0.0f, -2.0f), Vector3D(0.0f, 0.5f, 0.5f), Vector3D(0.225f, 0.225f, 0.225f));
	ball->enablePhysics();
	ball->getPhysics()->setVel(Vector3D(0.0f, 0.0f, 4.0f));
	mPoolBalls.push_back(ball);
	//mBall2->getPhysics()->setRotVel(Vector3D(0.83f, 0.13f, 0.74f) * SPIN_SPEED);

	ball = mpGraphicsSystem->createAndAddGameObject3D(mpSphere, Vector3D(2.0f, 0.0f, -2.0f), Vector3D(0.5f, 0.5f, 0.0f), Vector3D(0.225f, 0.225f, 0.225f));
	ball->enablePhysics();
	ball->getPhysics()->setVel(Vector3D(-4.0f, 0.0f, 0.0f));
	mPoolBalls.push_back(ball);
	
	mIsPaused = false;

	mpGraphicsSystem->getCamera()->setLoc(Vector3D(2.0f, 4.0f, 0.0f));
	mpGraphicsSystem->getCamera()->setRotation(Vector3D(65.0f, 0.0f, 0.0f));
	//mpGraphicsSystem->getCamera()->setRotation(Vector3D(45.0f, 20.0f, -20.0f));

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

	processCollisions();

	//mpGraphicsSystem->getAnimation(0)->update(mDeltaTime);

	float MAX_SPEED = 5.0f;
	//Limit the speed of the moving balls
	for (vector<GameObject3D*>::iterator i = mPoolBalls.begin(); i != mPoolBalls.end(); i++)
	{
		Vector3D currentVel = (*i)->getPhysics()->getVel();
		if (currentVel.length() > MAX_SPEED)
		{
			(*i)->getPhysics()->setVel(currentVel.normalized() * MAX_SPEED);
		}
	}

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

void Game::createPoolTable()
{

	mpGraphicsSystem->createAndAddGameObject3D(mpPlane, Vector3D(2.0f, -0.25f, -3.0f), Vector3D(0.0f, 0.5f, 0.0f), Vector3D(4.4f, 1.0f, 8.8f), Vector3D(0.0f, 90.0f, 0.0f));
	
	GameObject3D* wall;
	wall = mpGraphicsSystem->createAndAddGameObject3D(mpPlane, Vector3D(6.4f, -0.25f, -3.0f), Vector3D(0.5f, 0.5f, 0.0f), Vector3D(4.4f, 0.01f, 1.0f), Vector3D(90.0f, 90.0f, 0.0f));
	mWalls.push_back(wall);
	
	wall = mpGraphicsSystem->createAndAddGameObject3D(mpPlane, Vector3D(2.0f, -0.25f, -5.2f), Vector3D(0.5f, 0.5f, 0.0f), Vector3D(1.0f, 0.01f, 8.8f), Vector3D(90.0f, 0.0f, 90.0f));
	mWalls.push_back(wall);

	wall = mpGraphicsSystem->createAndAddGameObject3D(mpPlane, Vector3D(-2.4f, -0.25f, -3.0f), Vector3D(0.5f, 0.5f, 0.0f), Vector3D(4.4f, 0.01f, 1.0f), Vector3D(90.0f, 90.0f, 0.0f));
	mWalls.push_back(wall);

	wall = mpGraphicsSystem->createAndAddGameObject3D(mpPlane, Vector3D(2.0f, -0.25f, -0.8f), Vector3D(0.5f, 0.5f, 0.0f), Vector3D(1.0f, 0.01f, 8.8f), Vector3D(90.0f, 0.0f, 90.0f));
	mWalls.push_back(wall);
}

void Game::processCollisions()
{
	if (mpLine)
	{
		delete mpLine;
		mpLine = nullptr;
	}

	processBallCollisions();

	processWallCollisions();
	
	
}

void Game::processBallCollisions()
{
	for (vector<GameObject3D*>::iterator i = mPoolBalls.begin(); i != mPoolBalls.end() && i+1 != mPoolBalls.end(); i++)
	{
		for (vector<GameObject3D*>::iterator j = i + 1; j != mPoolBalls.end(); j++)
		{
			detectBallCollision(*i, *j);
		}
	}
}

void Game::detectBallCollision(GameObject3D* ball1, GameObject3D* ball2)
{
	//Check for Collision Detection between the two spheres... (We are assuming the scale is uniform on all axes, using one as radius)
	if ((ball1->getLoc() - ball2->getLoc()).length() < ball1->getScale().getX() + ball2->getScale().getX())
	{
		//Collision!

		Vector3D collisionDir = (ball2->getLoc() - ball1->getLoc()).normalized();
		//Create a line on the surface of ball1, with the length of the penetration
		Vector3D surfacePoint = ball1->getLoc() + (collisionDir * ball1->getScale().getX());
		float penetrationLength = ball1->getScale().getX() + ball2->getScale().getX() - (ball2->getLoc() - ball1->getLoc()).length();
		mpLine = new Mesh3D(surfacePoint, surfacePoint + collisionDir * penetrationLength);

		evaluateCollision(ball1, ball2, surfacePoint, collisionDir);
	}
}

void Game::evaluateCollision(GameObject3D* obj1, GameObject3D* obj2, Vector3D collisionPoint, Vector3D collisionNormal)
{
	PhysicsData3D* obj1phy = nullptr, *obj2phy = nullptr;
	
	obj1phy = obj1->getPhysics(); 
	
	if(obj2)
		obj2phy = obj2->getPhysics();

	float restitution = 0.0f;
	if (!obj2)
		restitution = 1.0f;

	Matrix3D collisionToWorldBasis;
	collisionToWorldBasis.setColumn(0, collisionNormal);

	collisionToWorldBasis.convertToColumnMajorOrthonormalBasis();

	Matrix3D worldToCollisionBasis = collisionToWorldBasis.transposed();
	
	//Change in velocity due to linear motion
	float deltaVelocity = obj1phy->getInverseMass();
	if(obj2)
		deltaVelocity += obj2phy->getInverseMass();

	Vector3D totalVelocity = obj1phy->getVel();
	if (obj2)
		totalVelocity += obj2phy->getVel();
	else if (totalVelocity == Vector3D::Zero())
		return;	//If the singular object isn't moving... No need to process a collision

	Vector3D contactVelocity = worldToCollisionBasis * totalVelocity;

	float desiredContactVelocity = -contactVelocity.getY() * (1.0f + restitution);

	Vector3D contactImpulse = Vector3D(desiredContactVelocity / contactVelocity.getY(), 0.0f, 0.0f);

	Vector3D impulse = collisionToWorldBasis * contactImpulse;

	Vector3D obj1VelocityChange = impulse * obj1phy->getInverseMass();

	Vector3D obj2VelocityChange;
	if(obj2)
		obj2VelocityChange = impulse * -1.0f * obj2phy->getInverseMass();

	//Lock objects along the Y axis
	obj1VelocityChange.setY(0.0f);
	obj2VelocityChange.setY(0.0f);

	obj1phy->setVel(obj1phy->getVel() + obj1VelocityChange);
	if(obj2)
		obj2phy->setVel(obj2phy->getVel() + obj2VelocityChange);
}

void Game::processWallCollisions()
{

	for (vector<GameObject3D*>::iterator i = mWalls.begin(); i != mWalls.end(); i++)
	{
		for (vector<GameObject3D*>::iterator j = mPoolBalls.begin(); j != mPoolBalls.end(); j++)
		{
			detectWallCollision(*i, *j);
		}
	}

}

void Game::detectWallCollision(GameObject3D* wall, GameObject3D* ball)
{
	//Check for Collision Detecion between a ball and a wall
	Vector4D ballLocCopy = Vector4D(ball->getLoc(), 1.0f);
	Matrix4D wallWorldToObjMatrix = wall->getWorldToObjMatrix();

	if (wallWorldToObjMatrix != Matrix4D::Zero())
	{
		Vector4D relBallPos = wallWorldToObjMatrix * ballLocCopy;
		assert(relBallPos.getW() == 1.0f);

		Vector4D relBallSize = Vector4D(ball->getScale(), 0.0f);
		relBallSize = wallWorldToObjMatrix * relBallSize;
		float relBallRadius = relBallSize.length();

		float ballRadius = ball->getScale().getX() / 2.0f;

		//if (mBall1->getLoc().getX() - mnXWall->getLoc().getX() < mBall1->getScale().getX())
		if (abs(relBallPos.getX()) < 0.5f
			&& abs(relBallPos.getY()) < relBallRadius
			&& abs(relBallPos.getZ()) < 0.5f)
		{
			//Collision!
			Vector3D collisionDir = (Vector4D(Vector3D::Up(), 0.0f) * wallWorldToObjMatrix).getVec3();
			collisionDir.normalize();
			//Collision direction could be backwards...
			if (relBallPos.getY() > 0)
				collisionDir *= -1.0f;

			//Create a line on the surface of ball1, with the length of the penetration
			Vector3D surfacePoint = ball->getLoc() + (collisionDir * ball->getScale().getX());

			evaluateCollision(ball, nullptr, surfacePoint, collisionDir);

		}
	}
}
#include "Game.h"
#include "Mesh2D.h"
#include "GraphicsSystem.h"
#include "ShaderProgram.h"
#include "Shader.h"

#include <assert.h>

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
		delete mspInstance;
}

Game::Game()
{
	mpBasicFragmentShader = nullptr;
	mpGraphicsSystem = nullptr;
	mpBasicShaderProgram = nullptr;
	mpTriangle = nullptr;
	mpBasicVertexShader = nullptr;

	mpTestFragmentShader = nullptr;
	mpTestVertexShader = nullptr;
	mpTestShaderProgram = nullptr;

	mpCurrentShaderProgram = nullptr;

	mInputLastF1State = false;
	mInputLastF2State = false;
	mInputLastF4State = false;
}

Game::~Game()
{

}

void Game::init()
{
	//Verticies for our triangle
	Vector2D verticies[] = {
		Vector2D(-0.5f, -0.5f),
		Vector2D(0.5f, -0.5f),
		Vector2D(0.5f, 0.5f),
		Vector2D(-0.5f, 0.5f)
	};

	unsigned int drawOrder[] = {
		0, 1, 2,
		2, 0, 3
	};

	mpTriangle = new Mesh2D(verticies, 4, drawOrder, 6);

	mpGraphicsSystem = GraphicsSystem::getInstance();

	assert(mpGraphicsSystem->init(800, 600));

	initShaderObjects();

	initShaderPrograms();

	mpCurrentShaderProgram = mpTestShaderProgram;
}

void Game::initShaderObjects()
{
	mpBasicVertexShader = new Shader(VERTEX_SHADER, "basic.vert");
	assert(mpBasicVertexShader->compile());

	mpBasicFragmentShader = new Shader(FRAGMENT_SHADER, "basic.frag");
	assert(mpBasicFragmentShader->compile());

	mpTestVertexShader = new Shader(VERTEX_SHADER, "test.vert");
	assert(mpTestVertexShader->compile());

	mpTestFragmentShader = new Shader(FRAGMENT_SHADER, "test.frag");
	assert(mpTestFragmentShader->compile());
}

void Game::initShaderPrograms()
{
	mpBasicShaderProgram = new ShaderProgram(mpBasicVertexShader, mpBasicFragmentShader);
	assert(mpBasicShaderProgram->linkProgram());

	mpBasicShaderProgram->setFloatAttribute(0, 3); //Sets Attribute 0 to a 3 dimentional float value


	mpTestShaderProgram = new ShaderProgram(mpTestVertexShader, mpTestFragmentShader);
	assert(mpTestShaderProgram->linkProgram());

	mpTestShaderProgram->setFloatAttribute(0, 3); //Sets Attribute 0 to a 3 dimentional float value
}

void Game::cleanup()
{
	//Cleanup Shader Programs
	delete mpBasicShaderProgram;
	mpBasicShaderProgram = nullptr;
	delete mpTestShaderProgram;
	mpTestShaderProgram = nullptr;

	mpCurrentShaderProgram = nullptr; // Don't Delete as this pointer has no ownership

	//Cleanup Shader Objects
	delete mpBasicVertexShader;
	mpBasicVertexShader = nullptr;
	delete mpBasicFragmentShader;
	mpBasicFragmentShader = nullptr;
	delete mpTestVertexShader;
	mpTestVertexShader = nullptr;
	delete mpTestFragmentShader;
	mpTestFragmentShader = nullptr;

	//Delete Mesh2D objects
	delete mpTriangle;
	mpTriangle = nullptr;

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
	return render();
}

void Game::input()
{
	bool keyState = mpGraphicsSystem->getKey(GraphicsSystem::Key::F1);
	if (keyState && !mInputLastF1State)
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
	mInputLastF1State = keyState;

	keyState = mpGraphicsSystem->getKey(GraphicsSystem::Key::F2);
	if (keyState && !mInputLastF2State)
	{
		if (mpCurrentShaderProgram == mpTestShaderProgram)
			mpCurrentShaderProgram = mpBasicShaderProgram;
		else
			mpCurrentShaderProgram = mpTestShaderProgram;
	}
	mInputLastF2State = keyState;

	keyState = mpGraphicsSystem->getKey(GraphicsSystem::Key::F4);
	if (keyState && !mInputLastF4State)
	{
		mpBasicVertexShader->reloadFromFile();
		mpBasicVertexShader->compile();
		mpBasicFragmentShader->reloadFromFile();
		mpBasicFragmentShader->compile();

		mpTestVertexShader->reloadFromFile();
		mpTestVertexShader->compile();
		mpTestFragmentShader->reloadFromFile();
		mpTestFragmentShader->compile();


		mpBasicShaderProgram->linkProgram();
		mpTestShaderProgram->linkProgram();
	}
	mInputLastF4State = keyState;
}

void Game::update()
{
	mpGraphicsSystem->setFloatUniform(*mpTestShaderProgram, "uTime", mpGraphicsSystem->getTime());
}

bool Game::render()
{
	mpGraphicsSystem->setActiveShaderProgram(*mpCurrentShaderProgram);

	mpGraphicsSystem->draw(*mpTriangle);

	return mpGraphicsSystem->render();
}
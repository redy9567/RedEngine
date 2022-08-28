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

}

Game::

void Game::init()
{
	//Verticies for our triangle
	Vector2D verticies[] = {
		Vector2D(-0.5f, -0.5f),
		Vector2D(0.5f, -0.5f),
		Vector2D(0.0f, 0.5f)
	};

	mpTriangle = new Mesh2D(verticies, 3);

	mpGraphicsSystem = GraphicsSystem::getInstance();

	assert(!mpGraphicsSystem->init(800, 600));

	mpVertexShader = new Shader(VERTEX_SHADER, "basic.vert");

	assert(mpVertexShader->compile());

	mpFragmentShader = new Shader(FRAGMENT_SHADER, "basic.frag");

	assert(mpFragmentShader->compile());

	mpShaderProgram = new ShaderProgram(mpVertexShader, mpVertexShader);
	mpShaderProgram->linkProgram();

	mpShaderProgram->setFloatAttribute(0, 3); //Sets Attribute 0 to a 3 dimentional float value
}

void Game::cleanup()
{
	//Cleanup Shader Program
	delete mpShaderProgram;
	mpShaderProgram = nullptr;

	//Cleanup Shader Objects
	delete mpVertexShader;
	mpVertexShader = nullptr;
	delete mpFragmentShader;
	mpFragmentShader = nullptr;

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
	render();
}

void Game::input()
{
	if (mpGraphicsSystem->debugProcessInput())
	{
		mpVertexShader->reloadFromFile();
		mpVertexShader->compile();
		mpFragmentShader->reloadFromFile();
		mpFragmentShader->compile();
		mpShaderProgram->linkProgram();
	}
}

void Game::update()
{

}

void Game::render()
{
	mpGraphicsSystem->setActiveShaderProgram(*mpShaderProgram);

	mpGraphicsSystem->draw(*mpTriangle);

	mpGraphicsSystem->render();
}
#include <iostream>
#include "GraphicsSystem.h"
#include "Mesh2D.h"
#include "Shader.h"
#include "ShaderProgram.h"

using namespace std;

int main()
{
	//Verticies for our triangle
	Vector2D verticies[] = { 
		Vector2D(-0.5f, -0.5f),
		Vector2D(0.5f, -0.5f),
		Vector2D(0.0f, 0.5f)
	};

	Mesh2D triangle = Mesh2D(verticies, 3);

	GraphicsSystem* graphicsSystem = GraphicsSystem::getInstance();

	if (!graphicsSystem->init(800, 600))
		return -1;

	Shader* myVertexShader = new Shader(VERTEX_SHADER, "basic.vert");

	bool success = myVertexShader->compile();

	if (!success)
	{
		return -1;
	}

	Shader* myFragmentShader = new Shader(FRAGMENT_SHADER, "basic.frag");

	success = myFragmentShader->compile();

	if (!success)
	{
		return -1;
	}

	ShaderProgram prog = ShaderProgram(myVertexShader, myFragmentShader);
	prog.linkProgram();

	/*
	//Cleanup Shader Objects
	delete myVertexShader;
	myVertexShader = nullptr;
	delete myFragmentShader;
	myFragmentShader = nullptr;
	*/

	prog.setFloatAttribute(0, 3); //Sets Attribute 0 to a 3 dimentional float value

	
	bool shouldContinue = true;
	//Render loop
	while (shouldContinue)
	{
		graphicsSystem->setActiveShaderProgram(prog);

		if (graphicsSystem->debugProcessInput())
		{
			myVertexShader->reloadFromFile();
			myVertexShader->compile();
			myFragmentShader->reloadFromFile();
			myFragmentShader->compile();
			prog.linkProgram();
		}

		//DELETE GET SPI FUNCTION
		graphicsSystem->draw(triangle);

		shouldContinue = graphicsSystem->render();
		
	}

	graphicsSystem->cleanup();
	GraphicsSystem::cleanupInstance();

	return 0;
}
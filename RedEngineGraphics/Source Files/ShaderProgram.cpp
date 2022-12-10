#include "ShaderProgram.h"
#include "GraphicsSystem.h"
#include "Shader.h"
#include <string>
#include <iostream>

using namespace std;

ShaderProgram::ShaderProgram()
{
	mSPI = GraphicsSystem::getInstance()->spCreateShaderProgram();
}

ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader)
{
	mSPI = GraphicsSystem::getInstance()->spCreateShaderProgram();

	attachShader(vertexShader);
	attachShader(fragmentShader);
}

ShaderProgram::~ShaderProgram()
{

}

void ShaderProgram::attachShader(Shader* shader)
{
	GraphicsSystem::getInstance()->spAttachShaderToProgram(mSPI, shader->mSOI);
}

bool ShaderProgram::linkProgram()
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	bool success = gs->spLinkProgram(mSPI);

	if (!success)
	{
		string infoLog = gs->spCollectDebugInfo(mSPI);
		cout << "Error: Shader Program Linking Failed:" << endl << infoLog << endl;
	}

	return success;
}

void ShaderProgram::activateFloatAttribute(int index, int dimensions)
{
	GraphicsSystem::getInstance()->spActivateFloatAttribute(index, dimensions);
}
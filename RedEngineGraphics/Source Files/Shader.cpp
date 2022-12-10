#include "Shader.h"
#include "GraphicsSystem.h"
#include <fstream>
#include <iostream>
#include <direct.h>

using namespace std;

Shader::Shader(SHADER_TYPE type, string filename)
{
	mType = type;

	mSOI = GraphicsSystem::getInstance()->sdCreateShader(type);

	mFilename = filename;
}

Shader::~Shader()
{
	GraphicsSystem::getInstance()->sdDeleteShader(mSOI);
}

bool Shader::loadFromFile()
{
	string filepath = "";

	switch (mType)
	{
	case VERTEX_SHADER:
		filepath = "../RedEngineGraphics/Vertex Shaders/";
		break;
	case FRAGMENT_SHADER:
		filepath = "../RedEngineGraphics/Fragment Shaders/";
	}

	filepath += mFilename;

	ifstream in = ifstream(filepath);
	string input = "";

	if (!in.is_open())
	{
		cout << "ERROR: SHADER FILEPATH \"" << filepath << "\" NOT FOUND!" << endl;
		return false;
	}

	string temp;
	while (!in.eof())
	{
		getline(in, temp);
		input += temp;
		input += "\n";
	}

	mCode = input;
	return true;
}

bool Shader::compile()
{
	GraphicsSystem* gs = GraphicsSystem::getInstance();

	bool success = gs->sdCompileShader(mSOI, mCode);

	if (!success)
	{
		string infoLog = gs->sdCollectDebugInfo(mSOI);
		cout << "Error: Vertex Shader Compilation Failed:" << endl << infoLog << endl;
	}

	return success;
}
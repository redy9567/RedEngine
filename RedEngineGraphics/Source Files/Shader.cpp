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
	//This later should be changed to one filepath, one being enabled by a command line arg, probably the external one
	string internalfilepath = "", externalFilepath = "";

	switch (mType)
	{
	case VERTEX_SHADER:
		internalfilepath = "./Vertex Shaders/";
		externalFilepath = "../RedEngineGraphics/Vertex Shaders/";
		break;
	case FRAGMENT_SHADER:
		internalfilepath = "./Fragment Shaders/";
		externalFilepath = "../RedEngineGraphics/Fragment Shaders/";
		break;
	}

	internalfilepath += mFilename;
	externalFilepath += mFilename;

	ifstream in = ifstream(internalfilepath);
	string input = "";

	if (!in.is_open())
	{
		//Attempting alternate filepath
		in.open(externalFilepath);

		if (!in.is_open())
		{
			cout << "ERROR: SHADER FILEPATH \"" << internalfilepath << "\" NOT FOUND!" << endl;
			return false;
		}
		
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
#include "ShaderManager.h"
#include "Shader.h"
#include "ShaderProgram.h"

using namespace std;

ShaderManager* ShaderManager::mspInstance = nullptr;

ShaderManager* ShaderManager::getInstance()
{
	if (!mspInstance)
		mspInstance = new ShaderManager();

	return mspInstance;
}

void ShaderManager::cleanupInstance()
{
	if (mspInstance)
	{
		delete mspInstance;
		mspInstance = nullptr;
	}
}

ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{

}

void ShaderManager::init()
{
	initDefaultShaders();
	initDefaultShaderPrograms();
}

void ShaderManager::cleanup()
{
	for (unordered_map<string, ShaderProgram*>::iterator it = mShaderPrograms.begin();
		it != mShaderPrograms.end(); it++)
	{
		delete it->second;
	}
	mShaderPrograms.clear();

	for (unordered_map<string, Shader*>::iterator it = mShaders.begin();
		it != mShaders.end(); it++)
	{
		delete it->second;
	}
	mShaders.clear();
}

bool ShaderManager::createAndAddShader(string key, SHADER_TYPE type, string filename)
{
	Shader* shader = new Shader(type, filename);

	bool success = shader->loadFromFile() && shader->compile();

	if(success)
		mShaders.emplace(key, shader);

	return success;
}

void ShaderManager::removeShader(string key)
{
	Shader* shader = mShaders.at(key);

	if (shader)
	{
		delete shader;
		mShaders.erase(key);
	}
}

bool ShaderManager::reloadShader(string key)
{
	Shader* shader = mShaders.at(key);

	bool success = shader ? shader->loadFromFile() && shader->compile() : false;

	return success;
}

void ShaderManager::createAndAddShaderProgram(string key)
{
	ShaderProgram* program = new ShaderProgram();

	mShaderPrograms.emplace(key, program);
}

bool ShaderManager::createAndAddShaderProgram(string key, string vertexShader, string fragmentShader)
{
	Shader* vs = mShaders.at(vertexShader);
	Shader* fs = mShaders.at(fragmentShader);

	if (vs && fs)
	{
		ShaderProgram* program = new ShaderProgram(vs, fs);

		mShaderPrograms.emplace(key, program);
		return true;
	}
	else
		return false;
}

void ShaderManager::removeShaderProgram(string key)
{
	ShaderProgram* program = mShaderPrograms.at(key);

	if (program)
	{
		delete program;
		mShaderPrograms.erase(key);
	}
}

bool ShaderManager::attachShaderToProgram(string programKey, string shaderKey)
{
	Shader* shader = mShaders.at(shaderKey);

	ShaderProgram* program = mShaderPrograms.at(programKey);

	if (shader && program)
	{
		program->attachShader(shader);
		return true;
	}
	else
		return false;
}

void ShaderManager::activateFloatAttributeOnProgram(string key, int index, int dimensions)
{
	ShaderProgram* program = mShaderPrograms.at(key);

	if (program)
		program->activateFloatAttribute(index, dimensions);
}

bool ShaderManager::linkShaderProgram(string key)
{
	ShaderProgram* program = mShaderPrograms.at(key);

	if (program)
		return program->linkProgram();
	else
		return false;
}

void ShaderManager::initDefaultShaders()
{
	createAndAddShader("Textured Vert", VERTEX_SHADER, "textured.vert");
	createAndAddShader("Textured Frag", FRAGMENT_SHADER, "textured.frag");
	createAndAddShader("Basic Vert", VERTEX_SHADER, "basic.vert");
	createAndAddShader("Basic UI Vert", VERTEX_SHADER, "basicUI.vert");
	createAndAddShader("Color Frag", FRAGMENT_SHADER, "color.frag");
	createAndAddShader("Text Vert", VERTEX_SHADER, "text.vert");
	createAndAddShader("Text Frag", FRAGMENT_SHADER, "text.frag");

	createAndAddShader("Basic3D Vert", VERTEX_SHADER, "basic3D.vert");

	createAndAddShader("Color Textured Frag", FRAGMENT_SHADER, "colorTextured.frag");
}

void ShaderManager::initDefaultShaderPrograms()
{
	createAndAddShaderProgram("Textured", "Textured Vert", "Textured Frag");
	linkShaderProgram("Textured");
	activateFloatAttributeOnProgram("Textured", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	createAndAddShaderProgram("Color", "Basic Vert", "Color Frag");
	linkShaderProgram("Color");
	activateFloatAttributeOnProgram("Color", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	createAndAddShaderProgram("ColorUI", "Basic UI Vert", "Color Frag");
	linkShaderProgram("ColorUI");
	activateFloatAttributeOnProgram("ColorUI", 0, 3); //Sets Attribute 0 to a 3 dimentional float value

	createAndAddShaderProgram("Text", "Text Vert", "Text Frag");
	linkShaderProgram("Text");

	createAndAddShaderProgram("ColorTextured", "Textured Vert", "Color Textured Frag");
	linkShaderProgram("ColorTextured");
	activateFloatAttributeOnProgram("ColorTextured", 0, 3);

	createAndAddShaderProgram("Basic3D", "Basic3D Vert", "Color Frag");
	linkShaderProgram("Basic3D");
	activateFloatAttributeOnProgram("Basic3D", 0, 3);
}
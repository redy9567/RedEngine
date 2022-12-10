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
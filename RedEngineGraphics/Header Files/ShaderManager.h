#pragma once
#include <Trackable.h>
#include <unordered_map>
#include <string>

class Shader;
class ShaderProgram;

enum SHADER_TYPE;

class ShaderManager : public Trackable
{

public:
	friend class GraphicsSystem;

	static ShaderManager* getInstance();
	static void cleanupInstance();

	void init();
	void cleanup();

	//Shaders
	bool createAndAddShader(std::string key, SHADER_TYPE type, std::string filename);
	void removeShader(std::string key);
	bool reloadShader(std::string key);

	//ShaderPrograms
	void createAndAddShaderProgram(std::string key);
	bool createAndAddShaderProgram(std::string key, std::string vertexShader, std::string fragmentShader);
	void removeShaderProgram(std::string key);
	bool attachShaderToProgram(std::string programKey, std::string shaderKey);
	void activateFloatAttributeOnProgram(std::string key, int index, int dimensions);
	bool linkShaderProgram(std::string key);

private:
	ShaderProgram* getShaderProgram(std::string key) { return mShaderPrograms.at(key); }

	ShaderManager();
	~ShaderManager();

	static ShaderManager* mspInstance;

	std::unordered_map<std::string, Shader*> mShaders;
	std::unordered_map<std::string, ShaderProgram*> mShaderPrograms;

};
#pragma once
#include <string>

typedef unsigned int ShaderObjectIndex;

enum SHADER_TYPE
{
	VERTEX_SHADER,
	FRAGMENT_SHADER
};

class Shader
{

public:
	friend class ShaderProgram;

	Shader(SHADER_TYPE type, std::string filename);
	~Shader();

	SHADER_TYPE getType() { return mType; }

	void reloadFromFile();
	bool compile();

private:
	void loadFromFile(std::string filename);

	Shader() = delete;

	std::string mFilename;
	SHADER_TYPE mType;
	std::string mCode;
	ShaderObjectIndex mSOI;

};
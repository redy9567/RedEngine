#pragma once
#include <string>
#include "Trackable.h"

typedef unsigned int ShaderObjectIndex;

enum SHADER_TYPE
{
	VERTEX_SHADER,
	FRAGMENT_SHADER
};

class Shader : public Trackable
{

public:
	friend class ShaderProgram;
	friend class ShaderManager;

private:
	Shader(SHADER_TYPE type, std::string filename);
	~Shader();

	SHADER_TYPE getType() { return mType; }

	bool compile();
	bool loadFromFile();

	Shader() = delete;

	std::string mFilename;
	SHADER_TYPE mType;
	std::string mCode;
	ShaderObjectIndex mSOI;

};
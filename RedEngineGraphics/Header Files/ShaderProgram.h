#pragma once
#include "Trackable.h"

typedef unsigned int ShaderProgramIndex;

class Shader;

class ShaderProgram : public Trackable
{

public:
	friend class GraphicsSystem;

	ShaderProgram();
	ShaderProgram(Shader* vertexShader, Shader* fragmentShader);
	~ShaderProgram();

	void attachShader(Shader* shader);

	void setFloatAttribute(int index, int dimensions);

	bool linkProgram();

private:
	ShaderProgramIndex mSPI;

};
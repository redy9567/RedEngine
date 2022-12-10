#pragma once
#include "Trackable.h"

typedef unsigned int ShaderProgramIndex;

class Shader;

class ShaderProgram : public Trackable
{

public:
	friend class GraphicsSystem;
	friend class ShaderManager;

private:
	ShaderProgram();
	ShaderProgram(Shader* vertexShader, Shader* fragmentShader);
	~ShaderProgram();

	void attachShader(Shader* shader);

	void activateFloatAttribute(int index, int dimensions);

	bool linkProgram();

	ShaderProgramIndex mSPI;

};
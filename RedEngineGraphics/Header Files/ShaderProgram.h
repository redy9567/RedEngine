#pragma once

typedef unsigned int ShaderProgramIndex;

class Shader;

class ShaderProgram
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
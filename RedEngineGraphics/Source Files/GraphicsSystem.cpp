#include "GraphicsSystem.h"
#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include <iostream>
#include "Mesh2D.h"
#include "Shader.h"
#include "ShaderProgram.h"

using namespace std;

GraphicsSystem* GraphicsSystem::mspInstance = nullptr;

GraphicsSystem* GraphicsSystem::getInstance()
{
	if (!mspInstance)
		mspInstance = new GraphicsSystem();

	return mspInstance;
}

void GraphicsSystem::cleanupInstance()
{
	if (mspInstance)
	{
		if (mspInstance->mInit)
			mspInstance->cleanup();

		delete mspInstance;
	}
		
}

GraphicsSystem::GraphicsSystem()
{
	mInit = false;
	mWindow = nullptr;
}

GraphicsSystem::~GraphicsSystem()
{
	if (mInit)
		cleanup();
}

bool GraphicsSystem::init(int displayWidth, int displayHeight)
{
	//Initialize OpenGL, and set our context
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create Window, and verify
	mWindow = glfwCreateWindow(displayWidth, displayHeight, "LearnOpenGL", NULL, NULL);
	if (!mWindow)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(mWindow);

	//Load glad, and verify
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return false;
	}

	//Tell OpenGL our rendering frame/viewport
	glViewport(0, 0, displayWidth, displayHeight);

	//Set our callback function for resizing the window
	glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);

	cout << "Well here we are!" << endl;

	mInit = true;
	return true;
}

void GraphicsSystem::cleanup()
{
	glfwTerminate();
	mInit = false;
}

bool GraphicsSystem::render()
{
	if (glfwWindowShouldClose(mWindow))
		return false;

	glfwSwapBuffers(mWindow);
	glfwPollEvents();
	return true;
}

void GraphicsSystem::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void GraphicsSystem::draw(Mesh2D& mesh)
{
	if (mesh.mVBO == -1)
	{
		//Setup Vertex Buffer Object (VBO)
		glGenBuffers(1, &mesh.mVBO);

		//Setup Vertex Array Object (VAO)
		glGenVertexArrays(1, &mesh.mVAO);

		//Bind VAO to OpenGL
		glBindVertexArray(mesh.mVAO);

		//Bind VBO to OpenGL
		glBindBuffer(GL_ARRAY_BUFFER, mesh.mVBO);

		unsigned int numOfFloats = 3 * (double)mesh.mVertexCount;

		float* verticies = new float[numOfFloats];

		for (int i = 0; i < mesh.mVertexCount; i++)
		{
			verticies[i * 3] = mesh.getVertexAt(i).getX();
			verticies[i * 3 + 1] = mesh.getVertexAt(i).getY();
			verticies[i * 3 + 2] = 0.0f;
		}

		//Copy data into bound buffer (VBO)
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numOfFloats, verticies, GL_STATIC_DRAW);

		delete[] verticies;
		verticies = nullptr;

		//Linking Vertex Attributes
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
	else
	{
		glBindVertexArray(mesh.mVAO);
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

ShaderObjectIndex GraphicsSystem::sdCreateShader(SHADER_TYPE type)
{
	switch (type)
	{
	case VERTEX_SHADER:
		return glCreateShader(GL_VERTEX_SHADER);
		break;
	case FRAGMENT_SHADER:
		return glCreateShader(GL_FRAGMENT_SHADER);
		break;
	}

	return -1;
}

bool GraphicsSystem::sdCompileShader(ShaderObjectIndex soi, string code)
{
	const char* charCode = code.c_str();
	//Attach the Vertex Shader Code and Compile
	glShaderSource(soi, 1, &charCode, NULL);
	glCompileShader(soi);

	int success;
	glGetShaderiv(soi, GL_COMPILE_STATUS, &success);

	return success;
}

string GraphicsSystem::sdCollectDebugInfo(ShaderObjectIndex soi)
{
	char infoLog[512];

	glGetShaderInfoLog(soi, 512, NULL, infoLog);

	return infoLog;
}

ShaderProgramIndex GraphicsSystem::spCreateShaderProgram()
{
	return glCreateProgram();
}

void GraphicsSystem::spAttachShaderToProgram(ShaderProgramIndex spi, ShaderObjectIndex soi)
{
	glAttachShader(spi, soi);
}

bool GraphicsSystem::spLinkProgram(ShaderProgramIndex spi)
{
	glLinkProgram(spi);

	int success;
	glGetProgramiv(spi, GL_LINK_STATUS, &success);

	return success;
}

string GraphicsSystem::spCollectDebugInfo(ShaderProgramIndex spi)
{
	char infoLog[512];

	glGetProgramInfoLog(spi, 512, NULL, infoLog);

	return infoLog;
}

void GraphicsSystem::sdDeleteShader(ShaderObjectIndex shader)
{
	glDeleteShader(shader);
}

void GraphicsSystem::spSetFloatAttribute(int index, int dimensions)
{
	glVertexAttribPointer(index, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(float), (void*)0);
	glEnableVertexAttribArray(index);
}

void GraphicsSystem::setActiveShaderProgram(ShaderProgram program)
{
	glUseProgram(program.mSPI);
}

bool GraphicsSystem::debugProcessInput()
{
	if (glfwGetKey(mWindow, GLFW_KEY_F4))
	{
		return true;
	}
	else
		return false;
}
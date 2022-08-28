#include "Mesh2D.h"

Mesh2D::Mesh2D(Vector2D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount)
{
	mVerticies = new Vector2D[vertexCount]();
	mVertexCount = vertexCount;

	for (int i = 0; i < vertexCount; i++)
	{
		mVerticies[i] = vertexArray[i];
	}

	mDrawOrder = new unsigned int[drawCount]();
	mDrawCount = drawCount;

	for (int i = 0; i < drawCount; i++)
	{
		mDrawOrder[i] = drawOrder[i];
	}

	mVBO = -1; //Not yet registered in OpenGL. GraphicsSystem will handle these
	mVAO = -1;
	mEBO = -1;
}

Mesh2D::~Mesh2D()
{
	delete[] mVerticies;
	mVerticies = nullptr;

	delete[] mDrawOrder;
	mDrawOrder = nullptr;
}
#include "Mesh2D.h"

Mesh2D::Mesh2D(Vector2D vertexArray[], unsigned int vertexCount)
{
	mVerticies = new Vector2D[vertexCount]();
	mVertexCount = vertexCount;

	for (int i = 0; i < vertexCount; i++)
	{
		mVerticies[i] = vertexArray[i];
	}

	mVBO = -1;
	mVAO = -1;
}

Mesh2D::~Mesh2D()
{
	delete[] mVerticies;
	mVerticies = nullptr;
}
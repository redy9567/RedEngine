#pragma once
#include "Vector2D.h"

typedef unsigned int VertexBufferIndex;
typedef unsigned int VertexArrayIndex;

class Mesh2D
{

public:
	friend class GraphicsSystem;

	Mesh2D(Vector2D vertexArray[], unsigned int vertexCount);
	~Mesh2D();

	Vector2D getVertexAt(int index) { return mVerticies[index]; }
	Vector2D& getAllVerticies() { return *mVerticies; };

	unsigned int getVertexCount() { return mVertexCount; }

private:
	Mesh2D() = delete;

	Vector2D* mVerticies;
	unsigned int mVertexCount;

	VertexBufferIndex mVBO;
	VertexArrayIndex mVAO;

};
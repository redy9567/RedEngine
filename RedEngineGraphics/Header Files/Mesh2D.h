#pragma once
#include "Vector2D.h"
#include "Trackable.h"

typedef unsigned int VertexBufferIndex;
typedef unsigned int VertexArrayIndex;
typedef unsigned int ElementBufferIndex;

class Mesh2D : public Trackable
{

public:
	friend class GraphicsSystem;

	Mesh2D(Vector2D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount);
	~Mesh2D();

	Vector2D getVertexAt(int index) { return mVerticies[index]; }
	Vector2D& getAllVerticies() { return *mVerticies; };

	unsigned int getVertexCount() { return mVertexCount; }

private:
	Mesh2D() = delete;

	Vector2D* mVerticies;
	unsigned int mVertexCount;

	unsigned int* mDrawOrder;
	unsigned int mDrawCount;

	VertexBufferIndex mVBO;
	VertexArrayIndex mVAO;
	ElementBufferIndex mEBO;

};
#pragma once
#include "Vector2D.h"
#include "Vector3D.h"
#include "Trackable.h"
#include "MeshType.h"

typedef unsigned int VertexBufferIndex;
typedef unsigned int VertexArrayIndex;
typedef unsigned int ElementBufferIndex;

class Texture2D;

class Mesh2D : public Trackable
{

public:
	friend class GraphicsSystem;

	Mesh2D(Vector2D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, MeshType meshType = MeshType::Triangles);
	Mesh2D(Vector2D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, Vector3D colorData[], MeshType meshType = MeshType::Triangles);
	Mesh2D(Vector2D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, Vector3D colorData[],
		Texture2D** textureData, unsigned int textureDataCount, Vector2D textureCoords[], MeshType meshType = MeshType::Triangles);
	~Mesh2D();

	Vector2D getVertexAt(int index) { return mVerticies[index]; }
	Vector2D& getAllVerticies() { return *mVerticies; };

	unsigned int getVertexCount() { return mVertexCount; }

private:
	Mesh2D() = delete;

	MeshType mMeshType;
	Vector2D* mVerticies;
	unsigned int mVertexCount;

	unsigned int* mDrawOrder;
	unsigned int mDrawCount;

	bool mHasColorData;
	Vector3D* mColorData;

	unsigned int mTextureDataCount;
	Texture2D** mTextureData;
	Vector2D* mTextureCoords;

	VertexBufferIndex mVBO;
	VertexArrayIndex mVAO;
	ElementBufferIndex mEBO;

};
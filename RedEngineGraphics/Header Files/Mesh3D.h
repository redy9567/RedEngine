#pragma once
#include "Vector2D.h"
#include "Vector3D.h"
#include "Trackable.h"
#include "MeshType.h"

typedef unsigned int VertexBufferIndex;
typedef unsigned int VertexArrayIndex;
typedef unsigned int ElementBufferIndex;

class Texture2D;

enum PrimitiveType
{
	Cube,
	Plane,
	Sphere, //Oh boy, spheres are complicated primitives!
	Skybox, //Not really a primitive, but definitely a hack because I'm lazy
	Line,
	None
};

class Mesh3D : public Trackable
{

public:
	friend class GraphicsSystem;

	Mesh3D(PrimitiveType type);
	Mesh3D(Vector3D linePoint1, Vector3D linePoint2);
	Mesh3D(Vector3D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, MeshType meshType = MeshType::Triangles);
	Mesh3D(Vector3D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, Vector3D colorData[], MeshType meshType = MeshType::Triangles);
	//Mesh3D(Vector3D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, Vector3D colorData[],
	//	Texture2D** textureData, unsigned int textureDataCount, Vector2D textureCoords[], MeshType meshType = Triangles);
	~Mesh3D();

	Vector3D getVertexAt(int index) { return mVerticies[index]; }
	Vector3D& getAllVerticies() { return *mVerticies; };

	unsigned int getVertexCount() { return mVertexCount; }

private:
	Mesh3D() = delete;

	void generateSphere();

	MeshType mMeshType;
	PrimitiveType mPrimitiveType;
	Vector3D* mVerticies;
	unsigned int mVertexCount;

	unsigned int* mDrawOrder;
	unsigned int mDrawCount;

	bool mHasColorData;
	Vector3D* mColorData;

	/* LETS Implement Textures later...
	unsigned int mTextureDataCount;
	Texture2D** mTextureData;
	Vector2D* mTextureCoords;
	*/

	VertexBufferIndex mVBO;
	VertexArrayIndex mVAO;
	ElementBufferIndex mEBO;

};
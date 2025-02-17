#include "Mesh3D.h"
#include "Texture2D.h"
#include "GraphicsSystem.h"
#include <assert.h>

Mesh3D::Mesh3D(PrimitiveType primitiveType)
{
	mPrimitiveType = primitiveType;

	switch (primitiveType)
	{
	case PrimitiveType::Cube:
		mVertexCount = 8;
		// 3 draws per triangle, 2 triangles per face, 6 faces on a cube... 3 * 2 * 6
		mDrawCount = 36;
		break;

	case PrimitiveType::Plane:
		mVertexCount = 4;
		// 3 draws per triangel, 2 triangles per face, 1 face on a plane...
		mDrawCount = 6;
		break;

	case PrimitiveType::None:
		assert(false);

	}
	
	mVerticies = new Vector3D[mVertexCount]();
	mDrawOrder = new unsigned int[mDrawCount]();

	switch (primitiveType)
	{
	case PrimitiveType::Cube:
		
		//Face 1: 0, 1, 2, 3	Face 2: 0, 1, 4, 5	Face 3: 0, 2, 4, 6
		//Face 4: 4, 5, 6, 7	Face 5: 2, 3, 6, 7	Face 6: 1, 3, 5, 7
		mVerticies[0] = Vector3D(0.0f, 0.0f, 0.0f);
		mVerticies[1] = Vector3D(1.0f, 0.0f, 0.0f);
		mVerticies[2] = Vector3D(0.0f, 1.0f, 0.0f);
		mVerticies[3] = Vector3D(1.0f, 1.0f, 0.0f);
		mVerticies[4] = Vector3D(0.0f, 0.0f, 1.0f);
		mVerticies[5] = Vector3D(1.0f, 0.0f, 1.0f);
		mVerticies[6] = Vector3D(0.0f, 1.0f, 1.0f);
		mVerticies[7] = Vector3D(1.0f, 1.0f, 1.0f);

		//Face 1
		mDrawOrder[0] = 0;
		mDrawOrder[1] = 1;
		mDrawOrder[2] = 2;
		mDrawOrder[3] = 2;
		mDrawOrder[4] = 1;
		mDrawOrder[5] = 3;

		//Face 2
		mDrawOrder[6] = 0;
		mDrawOrder[7] = 1;
		mDrawOrder[8] = 4;
		mDrawOrder[9] = 4;
		mDrawOrder[10] = 1;
		mDrawOrder[11] = 5;

		//Face 3
		mDrawOrder[12] = 0;
		mDrawOrder[13] = 2;
		mDrawOrder[14] = 4;
		mDrawOrder[15] = 4;
		mDrawOrder[16] = 2;
		mDrawOrder[17] = 6;

		//Face 4
		mDrawOrder[18] = 4;
		mDrawOrder[19] = 5;
		mDrawOrder[20] = 6;
		mDrawOrder[21] = 6;
		mDrawOrder[22] = 5;
		mDrawOrder[23] = 7;

		//Face 5
		mDrawOrder[24] = 2;
		mDrawOrder[25] = 3;
		mDrawOrder[26] = 6;
		mDrawOrder[27] = 6;
		mDrawOrder[28] = 3;
		mDrawOrder[29] = 7;

		//Face 6
		mDrawOrder[30] = 1;
		mDrawOrder[31] = 3;
		mDrawOrder[32] = 5;
		mDrawOrder[33] = 5;
		mDrawOrder[34] = 3;
		mDrawOrder[35] = 7;

		break;

	case PrimitiveType::Plane:
		mVerticies[0] = Vector3D(0.0f, 0.0f, 0.0f);
		mVerticies[1] = Vector3D(1.0f, 0.0f, 0.0f);
		mVerticies[2] = Vector3D(0.0f, 0.0f, 1.0f);
		mVerticies[3] = Vector3D(1.0f, 0.0f, 1.0f);

		mDrawOrder[0] = 0;
		mDrawOrder[1] = 1;
		mDrawOrder[2] = 2;
		mDrawOrder[3] = 2;
		mDrawOrder[4] = 1;
		mDrawOrder[5] = 3;
		break;

	case PrimitiveType::None:
		assert(false);
	}

	mVBO = -1; //Not yet registered in OpenGL. GraphicsSystem will handle these
	mVAO = -1;
	mEBO = -1;

	mHasColorData = false;
	mColorData = nullptr;
	mMeshType = MeshType::Triangles;
}

Mesh3D::Mesh3D(Vector3D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, MeshType meshType)
{
	mVerticies = new Vector3D[vertexCount]();
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

	mHasColorData = false;
	mColorData = nullptr;
	//mTextureDataCount = 0;
	//mTextureData = nullptr;
	mMeshType = meshType;
	mPrimitiveType = PrimitiveType::None;
}

Mesh3D::Mesh3D(Vector3D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, Vector3D colorData[], MeshType meshType)
	: Mesh3D(vertexArray, vertexCount, drawOrder, drawCount, meshType)
{

	mColorData = new Vector3D[vertexCount]();

	for (int i = 0; i < vertexCount; i++)
	{
		mColorData[i] = colorData[i];
	}

	mHasColorData = true;

	//mTextureDataCount = 0;
	//mTextureData = nullptr;

}

/*
Mesh2D::Mesh2D(Vector2D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, Vector3D colorData[],
	Texture2D** textureData, unsigned int textureDataCount, Vector2D textureCoords[], MeshType meshType)
	: Mesh2D(vertexArray, vertexCount, drawOrder, drawCount, colorData, meshType)
{
	mTextureData = new Texture2D * [textureDataCount];
	for (int i = 0; i < textureDataCount; i++)
	{
		mTextureData[i] = textureData[i];
		mTextureData[i]->mReferences++;
	}


	mTextureCoords = new Vector2D[vertexCount];

	for (int i = 0; i < vertexCount; i++)
	{
		mTextureCoords[i] = textureCoords[i];
	}

	mTextureDataCount = textureDataCount;

}
*/

Mesh3D::~Mesh3D()
{
	delete[] mVerticies;
	mVerticies = nullptr;

	delete[] mDrawOrder;
	mDrawOrder = nullptr;

	if (mHasColorData)
	{
		delete[] mColorData;
		mColorData = nullptr;
	}

	/*
	if (mTextureDataCount)
	{
		for (int i = 0; i < mTextureDataCount; i++)
		{
			mTextureData[i]->mReferences--;
		}
		mTextureData = nullptr;
		mTextureDataCount = 0;

		delete[] mTextureCoords;
	}
	*/

	GraphicsSystem::getInstance()->cleanupMesh3D(this);
}
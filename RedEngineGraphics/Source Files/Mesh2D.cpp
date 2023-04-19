#include "Mesh2D.h"
#include "Texture2D.h"

Mesh2D::Mesh2D(Vector2D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, MeshType meshType)
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

	mHasColorData = false;
	mColorData = nullptr;
	mTextureDataCount = 0;
	mTextureData = nullptr;
	mMeshType = meshType;
}

Mesh2D::Mesh2D(Vector2D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, Vector3D colorData[], MeshType meshType)
	: Mesh2D(vertexArray, vertexCount, drawOrder, drawCount, meshType)
{
	
	mColorData = new Vector3D[vertexCount]();

	for (int i = 0; i < vertexCount; i++)
	{
		mColorData[i] = colorData[i];
	}

	mHasColorData = true;

	mTextureDataCount = 0;
	mTextureData = nullptr;

}

Mesh2D::Mesh2D(Vector2D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, Vector3D colorData[],
	Texture2D** textureData, unsigned int textureDataCount, Vector2D textureCoords[], MeshType meshType)
	: Mesh2D(vertexArray, vertexCount, drawOrder, drawCount, colorData, meshType)
{
	mTextureData = new Texture2D*[textureDataCount];
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

Mesh2D::~Mesh2D()
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
}
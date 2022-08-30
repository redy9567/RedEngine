#include "Mesh2D.h"
#include "Texture2D.h"

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

	mHasColorData = false;
	mColorData = nullptr;
	mHasTextureData = false;
	mTextureData = nullptr;
}

Mesh2D::Mesh2D(Vector2D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, Vector3D colorData[])
	: Mesh2D(vertexArray, vertexCount, drawOrder, drawCount)
{
	
	mColorData = new Vector3D[vertexCount]();

	for (int i = 0; i < vertexCount; i++)
	{
		mColorData[i] = colorData[i];
	}

	mHasColorData = true;

	mHasTextureData = false;
	mTextureData = nullptr;

}

Mesh2D::Mesh2D(Vector2D vertexArray[], unsigned int vertexCount, unsigned int drawOrder[], unsigned int drawCount, Vector3D colorData[],
	Texture2D* textureData, Vector2D textureCoords[])
	: Mesh2D(vertexArray, vertexCount, drawOrder, drawCount, colorData)
{

	mTextureData = textureData;
	mTextureData->mReferences++;

	mTextureCoords = new Vector2D[vertexCount];

	for (int i = 0; i < vertexCount; i++)
	{
		mTextureCoords[i] = textureCoords[i];
	}

	mHasTextureData = true;

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

	if (mHasTextureData)
	{
		mTextureData->mReferences--;
		mTextureData = nullptr;
	}
}
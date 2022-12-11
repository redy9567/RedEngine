#include "Sprite.h"
#include "Mesh2D.h"
#include "Texture2D.h"

Sprite::Sprite(Texture2D** texture, Vector2D textureStartLoc, Vector2D loc, Vector2D size, float scale)
{
	//Square vertex definition
	Vector2D verticies[] = {
		Vector2D(-0.5f, -0.5f),
		Vector2D(0.5f, -0.5f),
		Vector2D(0.5f, 0.5f),
		Vector2D(-0.5f, 0.5f)
	};

	//Full Vertex Colors
	Vector3D vertexColors[] = {
		Vector3D(1.0f, 1.0f, 1.0f),
		Vector3D(1.0f, 1.0f, 1.0f),
		Vector3D(1.0f, 1.0f, 1.0f),
		Vector3D(1.0f, 1.0f, 1.0f)
	};

	Texture2D* tex = *texture;

	float normalizedWidth = size.getX() / tex->getWidth();
	float normalizedHeight = size.getY() / tex->getHeight();

	Vector2D normalizedTexureStart = Vector2D(textureStartLoc.getX() / tex->getWidth(), textureStartLoc.getY() / tex->getHeight());

	Vector2D textureCoords[]
	{
		normalizedTexureStart,
		normalizedTexureStart + Vector2D(normalizedWidth, 0.0f),
		normalizedTexureStart + Vector2D(normalizedWidth, normalizedHeight),
		normalizedTexureStart + Vector2D(0.0f, normalizedHeight)
	};

	//Vertex draw order
	unsigned int drawOrder[] = {
			0, 1, 2,
			2, 0, 3
	};

	mpMesh = new Mesh2D(verticies, 4, drawOrder, 6, vertexColors, texture, 1, textureCoords);

	mLoc = loc;
	mSize = size;
	mScale = scale;
}

Sprite::~Sprite()
{
	delete mpMesh;
}
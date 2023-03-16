#include "Sprite.h"
#include "Mesh2D.h"
#include "Texture2D.h"

Sprite::Sprite(Texture2D** texture, Vector2D textureStartLoc, Vector2D loc, Vector2D size, Vector2D scale)
{

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

	float aspect = size.getX() / size.getY();
	Vector2D verticies[4];

	if (aspect > 1.0f)
	{
		float normalizedSide = size.getY() / size.getX();
		//Horizontal Rectangle vertex definition
		verticies[0] = Vector2D(0.0f, 0.0f);
		verticies[1] = Vector2D(1.0f, 0.0f);
		verticies[2] = Vector2D(1.0f, normalizedSide);
		verticies[3] = Vector2D(0.0f, normalizedSide);
	}
	else if (aspect < 1.0f)
	{
		//Vertical Rectangle vertex definition
		verticies[0] = Vector2D(0.0f, 0.0f);
		verticies[1] = Vector2D(aspect, 0.0f);
		verticies[2] = Vector2D(aspect, 1.0f);
		verticies[3] = Vector2D(0.0f, 1.0f);
	}
	else
	{
		//Square vertex definition
		verticies[0] = Vector2D(0.0f, 0.0f);
		verticies[1] = Vector2D(1.0f, 0.0f);
		verticies[2] = Vector2D(1.0f, 1.0f);
		verticies[3] = Vector2D(0.0f, 1.0f);
	}
	
	mpMesh = new Mesh2D(verticies, 4, drawOrder, 6, vertexColors, texture, 1, textureCoords);

	mSize = size;
	mScale = scale;
}

Sprite::~Sprite()
{
	delete mpMesh;
}
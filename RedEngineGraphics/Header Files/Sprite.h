#pragma once
#include "Trackable.h"
#include "Vector2D.h"

class Mesh2D;
class Texture2D;

enum class ImageAnchor
{
	BottomLeft,
	Center
};

class Sprite : public Trackable
{
public:
	friend class GraphicsSystem;
	friend class SpriteManager;
	friend class AnimationData;

	Vector2D getSize() { return mSize; }
	Vector2D getScale() { return mScale; }

	void setSize(Vector2D size) { mSize = size; }
	void setScale(Vector2D scale) { mScale = scale; }
	
private:
	Sprite(Texture2D** texture, Vector2D textureStartLoc, Vector2D size, Vector2D scale = Vector2D::One(), ImageAnchor anchoring = ImageAnchor::Center);
	~Sprite();
	Sprite() = delete;

	Mesh2D* mpMesh;
	Vector2D mSize;
	Vector2D mScale;
	ImageAnchor mAnchoring;
};

#pragma once
#include "GameObject2D.h"
#include "Filepaths.h"
#include <string>

class Texture2D;
class AnimationData;

enum class Direction
{
	Up,
	Down,
	Left,
	Right
};

class UIElement : public GameObject2D
{

public:
	UIElement(std::string spriteTextureFilepath, std::string objectKey, Direction animationDirection, float distanceToMove, float speed, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr);
	UIElement(std::string textureFilepath, std::string objectKey, int animationColumns, int animationRows, Vector2D location = Vector2D::Zero());
	~UIElement();

	void setAnimating(bool hover) { mIsAnimating = hover; }
	bool getIsAnimating() { return mIsAnimating; }

	void update(float deltaTime);

private:
	bool mIsAnimating;
	Direction mAnimationDirection;

	Vector2D mOrigLoc;
	float mDistToMove;

	float mSpeed;
};

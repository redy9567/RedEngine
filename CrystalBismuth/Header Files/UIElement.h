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
	UIElement(std::string spriteTextureFilepath, std::string objectKey, Direction animationDirection, float distanceToMove, float speed, Vector2D location = Vector2D::Zero());
	UIElement(std::string textureFilepath, std::string objectKey, int animationColumns, int animationRows, Vector2D location = Vector2D::Zero());
	~UIElement();

	void setIsHovered(bool hover) { mIsHover = hover; }

	void update(float deltaTime);

private:
	Texture2D* mpTexture;
	AnimationData* mpAnimationData;
	Animation* mpAnimation;
	Sprite* mpSprite;

	bool mIsHover;
	Direction mAnimationDirection;

	Vector2D mOrigLoc;
	float mDistToMove;

	float mSpeed;
};

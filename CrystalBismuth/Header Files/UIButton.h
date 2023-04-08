#pragma once
#include "GameObject2D.h"
#include "Filepaths.h"
#include <string>

class Texture2D;
class AnimationData;

class UIButton : public GameObject2D
{

public:
	UIButton(Vector2D location = Vector2D::Zero(), bool codeAnimation = false);
	~UIButton();

	void setIsHovered(bool hover) { mIsHover = hover; }

	void update(float deltaTime);

private:
	Texture2D* mpTexture;
	AnimationData* mpAnimationData;
	Animation* mpAnimation;
	Sprite* mpSprite;

	bool mIsHover;

	Vector2D mOrigLoc;
	float mDistToMove;

};

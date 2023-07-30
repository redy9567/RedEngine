#pragma once
#include "GameObject2D.h"
#include <string>

class Texture2D;
class AnimationData;
class Sprite;

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
	friend class UIManager;

	UIElement(Sprite* sprite, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr);

	UIElement(std::string spriteTextureFilepath, std::string objectKey, Direction animationDirection, float distanceToMove, float speed, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr, bool animateOnHover = false);
	UIElement(std::string spriteTextureFilepath, std::string objectKey, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr);
	UIElement(std::string textureFilepath, std::string objectKey, int animationColumns, int animationRows, Vector2D location = Vector2D::Zero(), bool animateOnHover = false);
	UIElement(std::string objectKey, Vector2D location = Vector2D::Zero(), Vector2D scale = Vector2D::One(), GameObject2D* parent = nullptr);
	UIElement();
	~UIElement();

	void setAnimating(bool hover) { mIsAnimating = hover; }
	bool getIsAnimating() { return mIsAnimating; }
	UIElement* getParent() { return (UIElement*)mParent; }



	virtual void onClick(Vector2D mousePos) {};

	void update(float deltaTime);

private:
	bool mIsAnimating;
	bool mAnimateOnHover;
	Direction mAnimationDirection;

	Vector2D mOrigLoc;
	float mDistToMove;

	float mSpeed;
};

#pragma once
#include "UIElement.h"

enum class CursorMode
{
	None,
	SpriteImage
};

class Cursor : public UIElement
{
public:
	Cursor();
	~Cursor();

	void setImage(Sprite* sprite);

	void update(Vector2D mousePos);
};
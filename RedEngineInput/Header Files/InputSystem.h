#pragma once
#include "Trackable.h"
#include "Vector2D.h"
#include "MouseEvent.h"
#include <vector>
#include "KeyboardEvent.h"


class InputSystem : public Trackable
{

public:
	static InputSystem* getInstance();
	static void cleanupInstance();

	void update();

private:
	bool getMouseButton(MouseAction);
	bool getMouseButtonDown(MouseAction);
	bool getMouseButtonUp(MouseAction);

	Vector2D getMousePosition();

	void getKeyboardState();

	bool getKey(KeyCode);

	static InputSystem* mspInstance;

	bool mLeftClick, mRightClick, mMiddleClick;
	Vector2D mMousePos;

	std::vector<KeyCode> mPressedKeys;

};
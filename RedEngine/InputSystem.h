#pragma once
#include "Trackable.h"
#include "Vector2D.h"

enum KeyCode
{
	Key_A = 65,
	Key_B,
	Key_C,
	Key_D,
	Key_E,
	Key_F,
	Key_G,
	Key_H,
	Key_I,
	Key_J,
	Key_K,
	Key_L,
	Key_M,
	Key_N,
	Key_O,
	Key_P,
	Key_Q,
	Key_R,
	Key_S,
	Key_T,
	Key_U,
	Key_V,
	Key_W,
	Key_X,
	Key_Y,
	Key_Z,

	Key_Enter = 257,
	Key_Space = 32,
	Key_Escape = 256
};

class InputSystem : public Trackable
{

public:
	InputSystem();
	~InputSystem();

	bool getKeyDown(KeyCode key);
	bool getKeyUp(KeyCode key);
	bool getKey(KeyCode key);

	bool getMouseButtonDown(int button);
	bool getMouseButtonUp(int button);
	bool getMouseButton(int button);

	int getMouseX();
	int getMouseY();
	Vector2D getMousePosition();

private:
	

};
